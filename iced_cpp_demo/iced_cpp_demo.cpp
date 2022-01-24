// iced_cpp_demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <numeric>
#include <iostream>
#include <iomanip>
#include <sstream>

#define INSTR_INFO INSTR_INFO
#define OPCODE_INFO OPCODE_INFO
#define DECODER DECODER
#define ENCODER ENCODER
#define MVEX MVEX
#define NASM NASM
#define GAS GAS
#define BLOCK_ENCODER BLOCK_ENCODER
#define CODE_ASSEMBLER CODE_ASSEMBLER

#include "../iced_cpp/Intel/Assembler/Assembler.h"
#include "../iced_cpp/Intel/Assembler/AssemblerRegisters.h"
#include "../iced_cpp/Intel/Decoder.h"
#include "../iced_cpp/Intel/StreamCodeReader.h"
#include "../iced_cpp/Intel/StreamCodeWriter.h"
#include "../iced_cpp/Intel/ByteArrayCodeReader.h"
#include "../iced_cpp/Intel/NasmFormatter.h"
#include "../iced_cpp/Intel/StringOutput.h"
#include "../iced_cpp/Intel/ISymbolResolver.h"
#include "../iced_cpp/Intel/GasFormatter.h"
#include "../iced_cpp/Intel/InstructionInfoFactory.h"
#include "../iced_cpp/Intel/Iced.Intel.MemorySizeExtensions.h"

using namespace Iced::Intel::AssemblerRegisters;
using namespace Iced::Intel;

/*
 * This method produces the following output:
00007FFAC46ACDA4 48895C2410           mov       [rsp+10h],rbx
00007FFAC46ACDA9 4889742418           mov       [rsp+18h],rsi
00007FFAC46ACDAE 55                   push      rbp
00007FFAC46ACDAF 57                   push      rdi
00007FFAC46ACDB0 4156                 push      r14
00007FFAC46ACDB2 488DAC2400FFFFFF     lea       rbp,[rsp-100h]
00007FFAC46ACDBA 4881EC00020000       sub       rsp,200h
00007FFAC46ACDC1 488B0518570A00       mov       rax,[rel 7FFA`C475`24E0h]
00007FFAC46ACDC8 4833C4               xor       rax,rsp
00007FFAC46ACDCB 488985F0000000       mov       [rbp+0F0h],rax
00007FFAC46ACDD2 4C8B052F240A00       mov       r8,[rel 7FFA`C474`F208h]
00007FFAC46ACDD9 488D05787C0400       lea       rax,[rel 7FFA`C46F`4A58h]
00007FFAC46ACDE0 33FF                 xor       edi,edi
    */
void HowTo_Disassemble()
{
    const int HEXBYTES_COLUMN_BYTE_LENGTH = 10;
    const int exampleCodeBitness = 64;
    const std::uint64_t exampleCodeRIP = 0x00007FFAC46ACDA4;
    static const std::array codeBytes = std::to_array<std::uint8_t>({
        0x48, 0x89, 0x5C, 0x24, 0x10, 0x48, 0x89, 0x74, 0x24, 0x18, 0x55, 0x57, 0x41, 0x56, 0x48, 0x8D,
        0xAC, 0x24, 0x00, 0xFF, 0xFF, 0xFF, 0x48, 0x81, 0xEC, 0x00, 0x02, 0x00, 0x00, 0x48, 0x8B, 0x05,
        0x18, 0x57, 0x0A, 0x00, 0x48, 0x33, 0xC4, 0x48, 0x89, 0x85, 0xF0, 0x00, 0x00, 0x00, 0x4C, 0x8B,
        0x05, 0x2F, 0x24, 0x0A, 0x00, 0x48, 0x8D, 0x05, 0x78, 0x7C, 0x04, 0x00, 0x33, 0xFF
    });

    // You can also pass in a hex string, eg. "90 91 929394", or you can use your own CodeReader
    // reading data from a file or memory etc
    auto codeReader = ByteArrayCodeReader(codeBytes);
    auto decoder = Decoder::Create(exampleCodeBitness, &codeReader);
    decoder.SetIP(exampleCodeRIP);
    std::uint64_t endRip = decoder.GetIP() + (std::uint32_t)codeBytes.size();

    auto instructions = std::vector<Instruction>();
    while (decoder.GetIP() < endRip)
        instructions.push_back(decoder.Decode());

    // Formatters: Masm*, Nasm*, Gas* (AT&T) and Intel* (XED).
    // There's also `FastFormatter` which is ~2x faster. Use it if formatting speed is more
    // important than being able to re-assemble formatted instructions.
    auto formatter = NasmFormatter();
    formatter.GetOptions().SetDigitSeparator("`");
    formatter.GetOptions().SetFirstOperandCharIndex(10);
    auto output = StringOutput();
    for (const auto& instr : instructions)
    {
        // Don't use instr.ToString(), it allocates more, uses masm syntax and default options
        formatter.Format(instr, output);
        std::cout << std::hex << std::setw(16) << std::setfill('0') << std::uppercase << instr.GetIP() << " ";
        int instrLen = instr.GetLength();
        int byteBaseIndex = (int)(instr.GetIP() - exampleCodeRIP);
        for (int i = 0; i < instrLen; i++)
            std::cout << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (std::uint32_t)(std::uint8_t)codeBytes[byteBaseIndex + i];
        int missingBytes = HEXBYTES_COLUMN_BYTE_LENGTH - instrLen;
        std::cout << std::string(missingBytes * 2, ' ');
        std::cout << " ";
        std::cout << output.ToStringAndReset() << std::endl;
    }
}

/*
 * This method produces the following output:
1234567810000000 = push r15
1234567810000002 = add rax,r15
1234567810000005 = mov rax,[rax]
1234567810000008 = mov rax,[rax]
123456781000000B = cmp dword ptr [rax+rcx*8+10h],0FFFFFFFFh
1234567810000010 = jne short 123456781000003Dh
1234567810000012 = inc rax
1234567810000015 = lea rcx,[1234567810000040h]
123456781000001C = rep stosd
123456781000001E = xacquire lock add qword ptr [rax+rcx],7Bh
1234567810000025 = vaddpd zmm1{k3}{z},zmm2,zmm3{rz-sae}
123456781000002B = vunpcklps xmm2{k5}{z},xmm6,dword bcst [rax]
1234567810000031 = inc rax
1234567810000034 = je short 1234567810000031h
1234567810000036 = inc rcx
1234567810000039 = je short 123456781000003Ch
123456781000003B = nop
123456781000003C = nop
123456781000003D = pop r15
123456781000003F = ret
1234567810000040 = pause
     */
void HowTo_Assemble()
{
    // The assembler supports all modes: 16-bit, 32-bit and 64-bit.
    auto c = Assembler(64);

    auto label1 = c.CreateLabel();
    auto data1 = c.CreateLabel();

    c.push(r15);
    c.add(rax, r15);

    // If the memory operand can only have one size, __[] can be used. The assembler ignores
    // the memory size unless it's an ambiguous instruction, eg. 'add [mem],123'
    c.mov(rax, __[rax]);
    c.mov(rax, __qword_ptr[rax]);

    // The assembler must know the memory size to pick the correct instruction
    c.cmp(__dword_ptr[rax + rcx * 8 + 0x10], -1);
    c.jne(label1); // Jump to Label1

    c.inc(rax);

    // Labels can be referenced by memory operands (64-bit only) and call/jmp/jcc/loopcc instructions
    c.lea(rcx, __[data1]);

    // The assembler has prefix properties that will be added to the following instruction
    c.rep().stosd();
    c.xacquire().lock().add(__qword_ptr[rax + rcx], 123);

    // The assembler defaults to VEX instructions. If you need EVEX instructions, set PreferVex=false
    c.SetPreferVex(false);
    // or call `c.vex` or `c.evex` prefixes to override the default encoding.
    // AVX-512 decorators are properties on the memory and register operands
    c.vaddpd(zmm1.k3().z(), zmm2, zmm3.rz_sae());
    // To broadcast memory, use the __dword_bcst/__qword_bcst memory types
    c.vunpcklps(xmm2.k5().z(), xmm6, __dword_bcst[rax]);

    // You can create anonymous labels, just like in eg. masm, @@, @F and @B
    c.AnonymousLabel(); // same as @@: in masm
    c.inc(rax);
    c.je(c.B()); // reference the previous anonymous label
    c.inc(rcx);
    c.je(c.F()); // reference the next anonymous label
    c.nop();
    c.AnonymousLabel();
    c.nop();

    // Emit label1:
    c.Label(label1);
    c.pop(r15);
    c.ret();
    c.Label(data1);
    c.db((uint8_t)0xF3, (uint8_t)0x90); // pause

    const std::uint64_t RIP = 0x1234567810000000;

    auto ss = std::stringstream();
    auto streamCodeWriter = StreamCodeWriter(&ss);

    c.Assemble(streamCodeWriter, RIP);

    // Disassemble the result

    // Unnecessary for C++'s std::stringstream
    // stream.Seek(0, System::IO::SeekOrigin::Begin);

    auto reader = StreamCodeReader(&ss);
    auto decoder = Decoder::Create(64, &reader);

    std::size_t len = ((const std::stringstream&)(reader.GetStream())).str().length();

    decoder.SetIP(RIP);
    while (decoder.GetIP() < RIP + len)
    {
        std::cout << std::hex << std::uppercase << decoder.GetIP() << std::dec << " = ";
        Instruction instr;
        decoder.Decode(instr);
        std::cout << instr.ToString() << std::endl;
    }
}

void HowTo_SymbolResolver()
{
    class SymbolResolver final : public ISymbolResolver
    {
    private:
        const std::unordered_map<std::uint64_t, std::string> symbolDict;

    public:
        SymbolResolver(const std::unordered_map<std::uint64_t, std::string>& dict) : symbolDict(dict)
        {
        }

        virtual bool TryGetSymbol(const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, std::uint64_t address, std::int32_t addressSize, SymbolResult& symbol) const override
        {
            if (symbolDict.count(address))
            {
                symbol = SymbolResult(address, symbolDict.at(address));
                return true;
            }
            return false;
        }
    };

    // To-Do: Support string_view
    const auto symbols = std::unordered_map<std::uint64_t, std::string>
    {
         { 0x5AA55AA5UL, "my_data" },
    };

    auto symbolResolver = SymbolResolver(symbols);
    auto reader = ByteArrayCodeReader<std::string_view>::DecodeFromString("488B8AA55AA55A");
    auto decoder = Decoder::Create(64, &reader);
    Instruction instr;
    decoder.Decode(instr);

    auto formatter = GasFormatter(&symbolResolver);
    auto output = StringOutput();

    formatter.Format(instr, output);
    // Prints: mov my_data(%rdx),%rcx
    std::cout << output.ToStringAndReset() << std::endl;
}

/*
  * This method produces the following output:
00007FFAC46ACDA4 mov [rsp+10h],rbx
    OpCode: o64 89 /r
    Instruction: MOV r/m64, r64
    Encoding: Legacy
    Mnemonic: Mov
    Code: Mov_rm64_r64
    CpuidFeature: X64
    FlowControl: Next
    Displacement offset = 4, size = 1
    Memory size: 8
    Op0Access: Write
    Op1Access: Read
    Op0: r64_or_mem
    Op1: r64_reg
    Used reg: RSP:Read
    Used reg: RBX:Read
    Used mem: [SS:RSP+0x10;UInt64;Write]
00007FFAC46ACDA9 mov [rsp+18h],rsi
    OpCode: o64 89 /r
    Instruction: MOV r/m64, r64
    Encoding: Legacy
    Mnemonic: Mov
    Code: Mov_rm64_r64
    CpuidFeature: X64
    FlowControl: Next
    Displacement offset = 4, size = 1
    Memory size: 8
    Op0Access: Write
    Op1Access: Read
    Op0: r64_or_mem
    Op1: r64_reg
    Used reg: RSP:Read
    Used reg: RSI:Read
    Used mem: [SS:RSP+0x18;UInt64;Write]
00007FFAC46ACDAE push rbp
    OpCode: o64 50+ro
    Instruction: PUSH r64
    Encoding: Legacy
    Mnemonic: Push
    Code: Push_r64
    CpuidFeature: X64
    FlowControl: Next
    SP Increment: -8
    Op0Access: Read
    Op0: r64_opcode
    Used reg: RBP:Read
    Used reg: RSP:ReadWrite
    Used mem: [SS:RSP+0xFFFFFFFFFFFFFFF8;UInt64;Write]
00007FFAC46ACDAF push rdi
    OpCode: o64 50+ro
    Instruction: PUSH r64
    Encoding: Legacy
    Mnemonic: Push
    Code: Push_r64
    CpuidFeature: X64
    FlowControl: Next
    SP Increment: -8
    Op0Access: Read
    Op0: r64_opcode
    Used reg: RDI:Read
    Used reg: RSP:ReadWrite
    Used mem: [SS:RSP+0xFFFFFFFFFFFFFFF8;UInt64;Write]
00007FFAC46ACDB0 push r14
    OpCode: o64 50+ro
    Instruction: PUSH r64
    Encoding: Legacy
    Mnemonic: Push
    Code: Push_r64
    CpuidFeature: X64
    FlowControl: Next
    SP Increment: -8
    Op0Access: Read
    Op0: r64_opcode
    Used reg: R14:Read
    Used reg: RSP:ReadWrite
    Used mem: [SS:RSP+0xFFFFFFFFFFFFFFF8;UInt64;Write]
00007FFAC46ACDB2 lea rbp,[rsp-100h]
    OpCode: o64 8D /r
    Instruction: LEA r64, m
    Encoding: Legacy
    Mnemonic: Lea
    Code: Lea_r64_m
    CpuidFeature: X64
    FlowControl: Next
    Displacement offset = 4, size = 4
    Op0Access: Write
    Op1Access: NoMemAccess
    Op0: r64_reg
    Op1: mem
    Used reg: RBP:Write
    Used reg: RSP:Read
00007FFAC46ACDBA sub rsp,200h
    OpCode: o64 81 /5 id
    Instruction: SUB r/m64, imm32
    Encoding: Legacy
    Mnemonic: Sub
    Code: Sub_rm64_imm32
    CpuidFeature: X64
    FlowControl: Next
    Immediate offset = 3, size = 4
    RFLAGS Written: OF, SF, ZF, AF, CF, PF
    RFLAGS Modified: OF, SF, ZF, AF, CF, PF
    Op0Access: ReadWrite
    Op1Access: Read
    Op0: r64_or_mem
    Op1: imm32sex64
    Used reg: RSP:ReadWrite
00007FFAC46ACDC1 mov rax,[7FFAC47524E0h]
    OpCode: o64 8B /r
    Instruction: MOV r64, r/m64
    Encoding: Legacy
    Mnemonic: Mov
    Code: Mov_r64_rm64
    CpuidFeature: X64
    FlowControl: Next
    Displacement offset = 3, size = 4
    Memory size: 8
    Op0Access: Write
    Op1Access: Read
    Op0: r64_reg
    Op1: r64_or_mem
    Used reg: RAX:Write
    Used mem: [DS:0x7FFAC47524E0;UInt64;Read]
00007FFAC46ACDC8 xor rax,rsp
    OpCode: o64 33 /r
    Instruction: XOR r64, r/m64
    Encoding: Legacy
    Mnemonic: Xor
    Code: Xor_r64_rm64
    CpuidFeature: X64
    FlowControl: Next
    RFLAGS Written: SF, ZF, PF
    RFLAGS Cleared: OF, CF
    RFLAGS Undefined: AF
    RFLAGS Modified: OF, SF, ZF, AF, CF, PF
    Op0Access: ReadWrite
    Op1Access: Read
    Op0: r64_reg
    Op1: r64_or_mem
    Used reg: RAX:ReadWrite
    Used reg: RSP:Read
00007FFAC46ACDCB mov [rbp+0F0h],rax
    OpCode: o64 89 /r
    Instruction: MOV r/m64, r64
    Encoding: Legacy
    Mnemonic: Mov
    Code: Mov_rm64_r64
    CpuidFeature: X64
    FlowControl: Next
    Displacement offset = 3, size = 4
    Memory size: 8
    Op0Access: Write
    Op1Access: Read
    Op0: r64_or_mem
    Op1: r64_reg
    Used reg: RBP:Read
    Used reg: RAX:Read
    Used mem: [SS:RBP+0xF0;UInt64;Write]
00007FFAC46ACDD2 mov r8,[7FFAC474F208h]
    OpCode: o64 8B /r
    Instruction: MOV r64, r/m64
    Encoding: Legacy
    Mnemonic: Mov
    Code: Mov_r64_rm64
    CpuidFeature: X64
    FlowControl: Next
    Displacement offset = 3, size = 4
    Memory size: 8
    Op0Access: Write
    Op1Access: Read
    Op0: r64_reg
    Op1: r64_or_mem
    Used reg: R8:Write
    Used mem: [DS:0x7FFAC474F208;UInt64;Read]
00007FFAC46ACDD9 lea rax,[7FFAC46F4A58h]
    OpCode: o64 8D /r
    Instruction: LEA r64, m
    Encoding: Legacy
    Mnemonic: Lea
    Code: Lea_r64_m
    CpuidFeature: X64
    FlowControl: Next
    Displacement offset = 3, size = 4
    Op0Access: Write
    Op1Access: NoMemAccess
    Op0: r64_reg
    Op1: mem
    Used reg: RAX:Write
00007FFAC46ACDE0 xor edi,edi
    OpCode: o32 33 /r
    Instruction: XOR r32, r/m32
    Encoding: Legacy
    Mnemonic: Xor
    Code: Xor_r32_rm32
    CpuidFeature: INTEL386
    FlowControl: Next
    RFLAGS Cleared: OF, SF, CF
    RFLAGS Set: ZF, PF
    RFLAGS Undefined: AF
    RFLAGS Modified: OF, SF, ZF, AF, CF, PF
    Op0Access: Write
    Op1Access: None
    Op0: r32_reg
    Op1: r32_or_mem
    Used reg: RDI:Write
     */
void HowTo_InstructionInfo()
{
    const int exampleCodeBitness = 64;
    const std::uint64_t exampleCodeRIP = 0x00007FFAC46ACDA4;
    constexpr std::array exampleCode = std::to_array<std::uint8_t> ({
        0x48, 0x89, 0x5C, 0x24, 0x10, 0x48, 0x89, 0x74, 0x24, 0x18, 0x55, 0x57, 0x41, 0x56, 0x48, 0x8D,
        0xAC, 0x24, 0x00, 0xFF, 0xFF, 0xFF, 0x48, 0x81, 0xEC, 0x00, 0x02, 0x00, 0x00, 0x48, 0x8B, 0x05,
        0x18, 0x57, 0x0A, 0x00, 0x48, 0x33, 0xC4, 0x48, 0x89, 0x85, 0xF0, 0x00, 0x00, 0x00, 0x4C, 0x8B,
        0x05, 0x2F, 0x24, 0x0A, 0x00, 0x48, 0x8D, 0x05, 0x78, 0x7C, 0x04, 0x00, 0x33, 0xFF
    });

    auto codeReader = ByteArrayCodeReader(exampleCode);
    auto decoder = Decoder::Create(exampleCodeBitness, &codeReader);
    decoder.SetIP(exampleCodeRIP);

    // Use a factory to create the instruction info if you need register and
    // memory usage. If it's something else, eg. encoding, flags, etc, there
    // are properties on Instruction that can be used instead.
    auto instrInfoFactory = InstructionInfoFactory();

    Instruction instr;
    while (codeReader.GetCanReadByte())
    {
        decoder.Decode(instr);

        // Gets offsets in the instruction of the displacement and immediates and their sizes.
        // This can be useful if there are relocations in the binary. The encoder has a similar
        // method. This method must be called after Decode() and you must pass in the last
        // instruction Decode() returned.
        auto offsets = decoder.GetConstantOffsets(instr);

        std::cout << std::setw(16) << std::setfill('0') << std::hex << std::uppercase << instr.GetIP() << std::dec << " " << instr.ToString() << std::endl;

        const auto& opCode = instr.GetOpCode();

        const auto& info = instrInfoFactory.GetInfo(instr);

        auto fpuInfo = instr.GetFpuStackIncrementInfo();
        std::cout << "    OpCode: " << opCode.ToOpCodeString() << std::endl;
        std::cout << "    Instruction: " << opCode.ToInstructionString() << std::endl;
        std::cout << "    Encoding: " << Iced::Intel::ToString(instr.GetEncoding()) << std::endl;
        std::cout << "    Mnemonic: " << ToString(instr.GetMnemonic()) << std::endl;
        std::cout << "    Code: " << ToString(instr.GetCode()) << std::endl;
        std::cout << "    CpuidFeature: ";
        {
            const auto& features = instr.GetCpuidFeatures();
            std::cout << std::accumulate(
                std::next(features.begin()),
                features.end(),
                Iced::Intel::ToString(features[0]),
                [](const std::string& a, CpuidFeature b) {
                    return a + " and " + Iced::Intel::ToString(b);
                }
            );
        }
        std::cout << std::endl;
        std::cout << "    FlowControl: " << Iced::Intel::ToString(instr.GetFlowControl()) << std::endl;

        if (fpuInfo.WritesTop)
        {
            if (fpuInfo.Increment == 0)
                std::cout << "    FPU TOP: the instruction overwrites TOP";
            else
                std::cout << "    FPU TOP inc: " << fpuInfo.Increment;
            std::cout << "    FPU TOP cond write: " << std::boolalpha << fpuInfo.Conditional << std::noboolalpha << std::endl;
        }
        if (offsets.GetHasDisplacement())
            std::cout << "    Displacement offset = " << (std::uint32_t)offsets.DisplacementOffset << ", size = " << (std::uint32_t)offsets.DisplacementSize << std::endl;
        if (offsets.GetHasImmediate())
            std::cout << "    Immediate offset = " << (std::uint32_t)offsets.ImmediateOffset << ", size = " << (std::uint32_t)offsets.ImmediateSize << std::endl;
        if (offsets.GetHasImmediate2())
            std::cout << "    Immediate #2 offset = " << (std::uint32_t)offsets.ImmediateOffset2 << ", size = " << (std::uint32_t)offsets.ImmediateSize2 << std::endl;
        if (instr.IsStackInstruction())
            std::cout << "    SP Increment: " << instr.GetStackPointerIncrement() << std::endl;
        if (instr.GetConditionCode() != ConditionCode::None)
            std::cout << "    Condition code: " << Iced::Intel::ToString(instr.GetConditionCode()) << std::endl;
        if (instr.GetRflagsRead() != RflagsBits::None)
            std::cout << "    RFLAGS Read: " << ToString(instr.GetRflagsRead()) << std::endl;
        if (instr.GetRflagsWritten() != RflagsBits::None)
            std::cout << "    RFLAGS Written: " << ToString(instr.GetRflagsWritten()) << std::endl;
        if (instr.GetRflagsCleared() != RflagsBits::None)
            std::cout << "    RFLAGS Cleared: " << ToString(instr.GetRflagsCleared()) << std::endl;
        if (instr.GetRflagsSet() != RflagsBits::None)
            std::cout << "    RFLAGS Set: " << ToString(instr.GetRflagsSet()) << std::endl;
        if (instr.GetRflagsUndefined() != RflagsBits::None)
            std::cout << "    RFLAGS Undefined: " << ToString(instr.GetRflagsUndefined()) << std::endl;
        if (instr.GetRflagsModified() != RflagsBits::None)
            std::cout << "    RFLAGS Modified: " << ToString(instr.GetRflagsModified()) << std::endl;
        for (int i = 0; i < instr.GetOpCount(); i++)
        {
            auto opKind = instr.GetOpKind(i);
            if (opKind == OpKind::Memory) 
            {
                int size = MemorySizeExtensions::GetSize(instr.GetMemorySize());
                if (size != 0)
                    std::cout << "    Memory size: " << size << std::endl;
                break;
            }
        }
        for (int i = 0; i < instr.GetOpCount(); i++)
            std::cout << "    Op" << i << "Access: " << Iced::Intel::ToString(info.GetOpAccess(i)) << std::endl;
        for (int i = 0; i < opCode.GetOpCount(); i++)
            std::cout << "    Op" << i << ": " << Iced::Intel::ToString(opCode.GetOpKind(i)) << std::endl;
        // The returned iterator is a struct, nothing is allocated unless you box it
        for (const auto& regInfo : info.GetUsedRegisters())
            std::cout << "    Used reg: " << regInfo.ToString() << std::endl;
        for (const auto& memInfo : info.GetUsedMemory())
            std::cout << "    Used mem: " << memInfo.ToString() << std::endl;
    }
}

int main()
{
    std::array demos = std::to_array<void(*)(void)>({ HowTo_Disassemble, HowTo_Assemble, HowTo_SymbolResolver, HowTo_InstructionInfo });

    for (int i = 0; i < (int)demos.size(); ++i) 
    {
        std::cout << "Demo " << std::dec << i << ":\n";
        demos[i]();
        std::cout << std::string(20, '=') << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
