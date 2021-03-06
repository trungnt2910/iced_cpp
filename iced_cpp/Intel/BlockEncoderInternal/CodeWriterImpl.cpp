// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "CodeWriterImpl.h"
#include "../ThrowHelper.h"

namespace Iced::Intel::BlockEncoderInternal
{

	CodeWriterImpl::CodeWriterImpl(CodeWriter* codeWriter)
	{
		if (codeWriter == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_codeWriter();
		}
		this->codeWriter = codeWriter;
	}

	void CodeWriterImpl::WriteByte(std::uint8_t value)
	{
		BytesWritten++;
		codeWriter->WriteByte(value);
	}
}
