#pragma once

#include <csharp/exceptionhelper.h>
#include <csharp/primitives.h>

#include <iostream>
#include <any>

class Stream
{
private:
	std::ios_base* _stream;
	bool _canRead;
	bool _canWrite;
	bool _owns;

public:
	Stream(std::istream* is, bool owns = false) : _stream(is), _canRead(true), _canWrite(false), _owns(owns) {}
	Stream(std::ostream* os, bool owns = false) : _stream(os), _canRead(false), _canWrite(true), _owns(owns) {}
	Stream(std::iostream* ios, bool owns = false) : _stream(ios), _canRead(true), _canWrite(true), _owns(owns) {}

	inline void WriteByte(byte value) { if (!_canWrite) throw NotSupportedException(); reinterpret_cast<std::ostream*>(_stream)->put(value); }
	inline byte ReadByte() { if (!_canRead) throw NotSupportedException(); return reinterpret_cast<std::istream*>(_stream)->get(); }

	~Stream() { if (_owns) delete _stream; }
};

class Attribute {};
