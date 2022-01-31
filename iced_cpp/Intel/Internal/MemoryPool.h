#pragma once

#include <algorithm>
#include <array>
#include <span>
#include <type_traits>
#include <utility>
#include <vector>

namespace Iced::Intel::Internal
{
	class Relocatable;

	template <typename T>
	concept IRelocatable = std::is_convertible_v<T*, Relocatable*>;

	namespace Detail
	{
		template <typename T>
		class MemorySlot;
	}

	/// <summary>
	/// A data type whose member pointers are relocatable during copy.
	/// </summary>
	class Relocatable
	{
		template <std::size_t N, std::array<std::size_t, N> Sizes, IRelocatable... Types>
		friend class ArrayPool;
		template <IRelocatable... Types>
		friend class VectorPool;
		template <typename T>
		friend class Detail::MemorySlot;
	protected:
		virtual constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info)
		{
		}
	};

	namespace Detail
	{
		template <typename T>
		/// <summary>
		/// Just the std::optional, but we know that the value is assigned once
		/// so we don't wanna waste the extra boolean.
		/// </summary>
		class MemorySlot
		{
		private:
			struct Empty
			{
				constexpr Empty() = default;
				constexpr ~Empty() = default;
			};
			union
			{
				Empty e = Empty();
				T value;
			};
		public:
			constexpr operator T& ()
			{
				return value;
			}
			constexpr operator const T& () const
			{
				return value;
			}
			constexpr T& operator=(const T& other)
			{
				std::construct_at(&value, other);
				return value;
			}
			constexpr T* operator&()
			{
				return &value;
			}
			constexpr const T* operator&() const
			{
				return &value;
			}
			constexpr std::enable_if_t<std::is_base_of_v<Relocatable, T>, void>
				Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info)
			{
				return value.Relocate(info);
			}
		};

		template <IRelocatable... Types>
		class VectorPoolImpl : public std::vector<Types>...
		{
		public:
			constexpr VectorPoolImpl() = default;
		};

		template <typename T, std::size_t N>
		consteval std::enable_if_t<(N > 0), std::array<T, N - 1>>
			SkipFirst(const std::array<T, N>& arr)
		{
			auto result = std::array<T, N - 1>();
			std::copy(arr.begin() + 1, arr.end(), result.begin());
			return result;
		}

		template <std::size_t N, std::array<std::size_t, N> Sizes, IRelocatable Type, IRelocatable... Other>
		class ArrayPoolImpl : public std::array<MemorySlot<Type>, Sizes.at(0)>, public ArrayPoolImpl<N - 1, SkipFirst(Sizes), Other...>
		{
		public:
			constexpr ArrayPoolImpl() = default;
		};

		template <std::array<std::size_t, 1> Sizes, IRelocatable Type>
		class ArrayPoolImpl<1, Sizes, Type> : public std::array<MemorySlot<Type>, Sizes.at(0)>
		{
		public:
			constexpr ArrayPoolImpl() = default;
		};
	}

	template <IRelocatable... Types>
	class VectorPool
	{
	private:
		Detail::VectorPoolImpl<Types...> pool;
	public:
		constexpr VectorPool() = default;

		template <IRelocatable T, typename... ConstructArgs>
		constexpr std::enable_if_t<std::disjunction_v<std::is_same<T, Types>...>, T*>
			Construct(ConstructArgs&&... args)
		{
			return &(((std::vector<T>&)pool).emplace_back(args...));
		}

		template <IRelocatable T>
		constexpr std::enable_if_t<std::disjunction_v<std::is_same<T, Types>...>, std::span<T>>
			GetData()
		{
			return std::span(((std::vector<T>&)pool).data(), ((std::vector<T>&)pool).size());
		}

		template <IRelocatable T>
		constexpr std::enable_if_t<std::disjunction_v<std::is_same<T, Types>...>, std::span<const T>>
			GetData() const
		{
			return std::span(((const std::vector<T>&)pool).data(), ((const std::vector<T>&)pool).size());
		}

		constexpr std::array<std::size_t, sizeof...(Types)>
			GetSizes() const
		{
			return std::to_array<std::size_t>({ ((const std::vector<Types>)pool).size()... });
		}
	};

	namespace Detail
	{
		template <typename T, typename... Other>
		struct IndexInPack;

		template <typename T, typename... Other>
		struct IndexInPack<T, T, Other...> : std::integral_constant<std::size_t, 0> {};

		template <typename T, typename U, typename... Other>
		struct IndexInPack<T, U, Other...> : std::integral_constant<std::size_t, 1 + IndexInPack<T, Other...>::value> {};

		template <typename T, typename... Other>
		inline constexpr std::size_t IndexInPackValue = IndexInPack<T, Other...>::value;
	}

	template <std::size_t N, std::array<std::size_t, N> Sizes, IRelocatable... Types>
	class ArrayPool
	{
		static_assert(Sizes.size() == sizeof...(Types), "Invalid number of types.");
	private:
		Detail::ArrayPoolImpl<N, Sizes, Types...> pool;
		std::array<std::size_t, Sizes.size()> currentSizes = { 0 };
		template <typename T>
		using MemberArray = std::array<Detail::MemorySlot<T>, Sizes[Detail::IndexInPackValue<T, Types...>]>;
	public:
		constexpr ArrayPool() = default;

		constexpr ArrayPool(const ArrayPool<N, Sizes, Types...>& other)
			: pool(other.pool), currentSizes(other.currentSizes)
		{
			auto rebaseInfo = std::vector<std::pair<const Relocatable*, const Relocatable*>>();

			const auto Populate = [&]<IRelocatable T>(const std::span<const T>&s)
			{
				auto& currentPool = (MemberArray<T>&)pool;
				for (std::size_t i = 0; i < currentPool.size(); ++i)
				{
					rebaseInfo.emplace_back(&s[i], &currentPool[i]);
				}
				// We need this dummy return value, read the next few lines.
				return 0;
			};

			// To expand templates this way, 
			// stuff must be some comma separated list.
			// Therefore we're creating a dummy array here.
			(void)std::to_array({ Populate(other.template GetData<Types>())... });

			const auto Relocate = [&]<IRelocatable T>()
			{
				auto& currentPool = (MemberArray<T>&)pool;
				for (std::size_t i = 0; i < currentPool.size(); ++i)
				{
					currentPool[i].Relocate(rebaseInfo);
				}
				return 0;
			};

			(void)std::to_array({ Relocate.template operator() < Types > ... });
		}

		constexpr std::vector<std::pair<const Relocatable*, const Relocatable*>>
			GetRelocInfo(const VectorPool<Types...>& other) const
		{
			auto rebaseInfo = std::vector<std::pair<const Relocatable*, const Relocatable*>>();

			const auto Populate = [&]<IRelocatable T>(const std::span<const T>&s)
			{
				auto& currentPool = (MemberArray<T>&)pool;
				for (std::size_t i = 0; i < currentPool.size(); ++i)
				{
					rebaseInfo.emplace_back(&s[i], &currentPool[i]);
				}
				return 0;
			};

			(void)std::to_array({ Populate(other.template GetData<Types>())... });

			return rebaseInfo;
		}

		constexpr ArrayPool(const VectorPool<Types...>& other)
		{
			auto rebaseInfo = GetRelocInfo(other);

			const auto Relocate = [&]<IRelocatable T>(const std::span<const T>&s)
			{
				auto& currentPool = (MemberArray<T>&)pool;
				std::size_t typeIndex = Detail::IndexInPackValue<T, Types...>;
				for (std::size_t i = 0; i < currentPool.size(); ++i)
				{
					currentPool[i] = s[i];
					currentPool[i].Relocate(rebaseInfo);
					++currentSizes[typeIndex];
				}
				return 0;
			};

			(void)std::to_array({ Relocate(other.template GetData<Types>())... });
		}

		template <IRelocatable T, typename... ConstructArgs>
		constexpr std::enable_if_t<std::disjunction_v<std::is_same<T, Types>...>, T*>
			Construct(ConstructArgs&&... args)
		{
			constexpr std::size_t typeIndex = IndexInPackValue<T, Types...>;
			std::size_t elementIndex = currentSizes[typeIndex];
			((MemberArray<T>&)pool)[elementIndex] = T(args...);
			++currentSizes[typeIndex];
			return &get<T>(((MemberArray<T>&)pool)[elementIndex]);
		}

		//template <IRelocatable T>
		//constexpr std::enable_if_t<std::disjunction_v<std::is_same<T, Types>...>, std::span<T>>
		//	GetData()
		//{
		//	return std::span(((MemberArray<T>&)pool).data(), ((MemberArray<T>&)pool).size());
		//}

		//template <IRelocatable T>
		//constexpr std::enable_if_t<std::disjunction_v<std::is_same<T, Types>...>, std::span<const T>>
		//	GetData() const
		//{
		//	return std::span(((const MemberArray<T>&)pool).data(), ((const MemberArray<T>&)pool).size());
		//}

		constexpr std::array<std::size_t, sizeof...(Types)>
			GetSizes() const
		{
			return Sizes;
		}
	};
}