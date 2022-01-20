#pragma once

namespace Iced::Intel
{
	// This class exists as std::touppper and std::tolower 
	// have their own problems.
	class CharHelpers
	{
	public:
		static constexpr char ToUpper(char ch)
		{
			return (('a' <= ch) && (ch <= 'z')) ? 'A' + (ch - 'a') : ch;
		}
		static constexpr char ToLower(char ch)
		{
			return (('A' <= ch) && (ch <= 'Z')) ? 'a' + (ch - 'A') : ch;
		}
	};
}