// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>
#include <csharp/interfaces.h>
#include <csharp/primitives.h>

// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "InstructionInfo.h"
#include "InstructionInfoInternal/InfoHandlerFlags.h"
#include "ThrowHelper.h"

using namespace Iced::Intel::InstructionInfoInternal;

namespace Iced::Intel
{

	InstructionInfo::InstructionInfo(bool dummy)
	{
		usedRegisters = SimpleList<UsedRegister>(std::vector<UsedRegister>(InstrInfoConstants::DefaultUsedRegisterCollCapacity));
		usedMemoryLocations = SimpleList<UsedMemory>(std::vector<UsedMemory>(InstrInfoConstants::DefaultUsedMemoryCollCapacity));
		//C# TO C++ CONVERTER TODO TASK: C# 'unsafe' code is not converted by C# to C++ Converter:
		//	 unsafe
			//   {
			//	opAccesses[0] = 0;
			//	opAccesses[1] = 0;
			//	opAccesses[2] = 0;
			//	opAccesses[3] = 0;
			//	opAccesses[4] = 0;
			//	Static.Assert(IcedConstants.MaxOpCount == 5 ? 0 : -1);
			//   }
	}

	InstructionInfo::UsedRegisterIterator InstructionInfo::GetUsedRegisters()
	{
		return UsedRegisterIterator(usedRegisters.Array, static_cast<std::uint32_t>(usedRegisters.ValidLength));
	}

	InstructionInfo::UsedMemoryIterator InstructionInfo::GetUsedMemory()
	{
		return UsedMemoryIterator(usedMemoryLocations.Array, static_cast<std::uint32_t>(usedMemoryLocations.ValidLength));
	}

	InstructionInfo::UsedRegisterIterator::UsedRegisterIterator(std::vector<UsedRegister>& usedRegisters, std::uint32_t length)
	{
		this->usedRegisters = usedRegisters;
		this->length = length;
		index = -1;
	}

	InstructionInfo::UsedRegisterIterator InstructionInfo::UsedRegisterIterator::GetEnumerator()
	{
		return *this;
	}

	UsedRegister InstructionInfo::UsedRegisterIterator::GetCurrent() const
	{
		return usedRegisters[index];
	}

	bool InstructionInfo::UsedRegisterIterator::MoveNext()
	{
		index++;
		return static_cast<std::uint32_t>(index) < length;
	}

	IEnumerator<UsedRegister>* InstructionInfo::UsedRegisterIterator::IEnumerable_GetEnumerator()
	{
		return begin();
	}

	System::Collections::IEnumerator* InstructionInfo::UsedRegisterIterator::IEnumerable_GetEnumerator()
	{
		return begin();
	}

	bool InstructionInfo::UsedRegisterIterator::IEnumerator_MoveNext()
	{
		return MoveNext();
	}

	void InstructionInfo::UsedRegisterIterator::Reset()
	{
		throw NotSupportedException();
	}

	InstructionInfo::UsedRegisterIterator::~UsedRegisterIterator()
	{
	}

	InstructionInfo::UsedMemoryIterator::UsedMemoryIterator(std::vector<UsedMemory>& usedMemoryLocations, std::uint32_t length)
	{
		this->usedMemoryLocations = usedMemoryLocations;
		this->length = length;
		index = -1;
	}

	InstructionInfo::UsedMemoryIterator InstructionInfo::UsedMemoryIterator::GetEnumerator()
	{
		return *this;
	}

	UsedMemory InstructionInfo::UsedMemoryIterator::GetCurrent() const
	{
		return usedMemoryLocations[index];
	}

	bool InstructionInfo::UsedMemoryIterator::MoveNext()
	{
		index++;
		return static_cast<std::uint32_t>(index) < length;
	}

	IEnumerator<UsedMemory>* InstructionInfo::UsedMemoryIterator::IEnumerable_GetEnumerator()
	{
		return begin();
	}

	System::Collections::IEnumerator* InstructionInfo::UsedMemoryIterator::IEnumerable_GetEnumerator()
	{
		return begin();
	}

	bool InstructionInfo::UsedMemoryIterator::IEnumerator_MoveNext()
	{
		return MoveNext();
	}

	void InstructionInfo::UsedMemoryIterator::Reset()
	{
		throw NotSupportedException();
	}

	InstructionInfo::UsedMemoryIterator::~UsedMemoryIterator()
	{
	}

	OpAccess InstructionInfo::GetOp0Access() const
	{
		//C# TO C++ CONVERTER TODO TASK: C# 'unsafe' code is not converted by C# to C++ Converter:
		//	 unsafe
			//	{
			//	 return (OpAccess)opAccesses[0];
			//	}
	}

	OpAccess InstructionInfo::GetOp1Access() const
	{
		//C# TO C++ CONVERTER TODO TASK: C# 'unsafe' code is not converted by C# to C++ Converter:
		//	 unsafe
			//	{
			//	 return (OpAccess)opAccesses[1];
			//	}
	}

	OpAccess InstructionInfo::GetOp2Access() const
	{
		//C# TO C++ CONVERTER TODO TASK: C# 'unsafe' code is not converted by C# to C++ Converter:
		//	 unsafe
			//	{
			//	 return (OpAccess)opAccesses[2];
			//	}
	}

	OpAccess InstructionInfo::GetOp3Access() const
	{
		//C# TO C++ CONVERTER TODO TASK: C# 'unsafe' code is not converted by C# to C++ Converter:
		//	 unsafe
			//	{
			//	 return (OpAccess)opAccesses[3];
			//	}
	}

	OpAccess InstructionInfo::GetOp4Access() const
	{
		//C# TO C++ CONVERTER TODO TASK: C# 'unsafe' code is not converted by C# to C++ Converter:
		//	 unsafe
			//	{
			//	 return (OpAccess)opAccesses[4];
			//	}
	}

	OpAccess InstructionInfo::GetOpAccess(std::int32_t operand)
	{
		switch (operand)
		{
		case 0:
			return GetOp0Access();
		case 1:
			return GetOp1Access();
		case 2:
			return GetOp2Access();
		case 3:
			return GetOp3Access();
		case 4:
			return GetOp4Access();
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_operand();
			return 0;
		}
	}
}
