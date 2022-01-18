#pragma once

#include "CodeReader.h"

#include <istream>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Code reader from a <see cref="System.IO.Stream"/>. 
	/// </summary>
	class StreamCodeReader final : public CodeReader
	{
		/// <summary>
		/// The stream this instance is writing to
		/// </summary>
		std::istream* _stream;

		bool _owns;
		/// <summary>
		/// Creates a new instance of <see cref="StreamCodeReader"/>. 
		/// </summary>
		/// <param name="stream">The input stream</param>
	public:
		StreamCodeReader(std::istream* stream, bool owns = false) : _stream(stream), _owns(owns) { }
		/// <summary>
		/// Reads the next byte or returns less than 0 if there are no more bytes
		/// </summary>
		/// <returns></returns>
		std::int32_t ReadByte() override { return _stream->get(); }

		std::istream& GetStream() { return *_stream; }

		~StreamCodeReader() { if (_owns) delete _stream; }
	};
}
