#pragma once

#include "CodeWriter.h"

#include <ostream>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Code writer to a <see cref="System.IO.Stream"/>. 
	/// </summary>
	class StreamCodeWriter final : public CodeWriter
	{
	private:
		/// <summary>
		/// The stream this instance is writing to
		/// </summary>
		std::ostream* _stream;

		bool _owns;

		/// <summary>
		/// Creates a new instance of <see cref="StreamCodeWriter"/>. 
		/// </summary>
		/// <param name="stream">The output stream</param>
	public:
		StreamCodeWriter(std::ostream* stream, bool owns = false) : _stream(stream), _owns(owns) { }
		/// <summary>
		/// Writes the next byte
		/// </summary>
		/// <param name="value">Value</param>
		void WriteByte(std::uint8_t value) override { _stream->put(value); }

		std::ostream& GetStream() { return *_stream; }

		~StreamCodeWriter() { if (_owns) delete _stream; }
	};
}
