#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_STX : public testing::Test
{
public:
    uint8_t mem[0xFFFF];
	Core6502::CPU *cpu;
    
	virtual void SetUp()
	{  
        // Create CPU
        cpu = new Core6502::CPU(mem);
	}

	virtual void TearDown()
	{
        delete cpu;
	}
};

// Checks all STX instructions

// STX Zero Page
TEST_F(Core6502Tests_STX, Test_STX_Zero_Page) {
    
    // Create test values
    uint8_t opCode = 0x86;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t xTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->registers.X = xTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check address has been set to X Register value
    EXPECT_EQ(cpu->mem[addr],xTestVal);

}

// STX Zero Page Y
TEST_F(Core6502Tests_STX, Test_STX_Zero_Page_Y) {
    
    // Create test values
    uint8_t opCode = 0x96;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t yVal = 0x10;
    uint8_t addr = zeroPageAddr + yVal;
    uint8_t xTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->registers.X = xTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check address has been set to X Register value
    EXPECT_EQ(cpu->mem[addr],xTestVal);

}

// STX Absolute
TEST_F(Core6502Tests_STX, Test_STX_Absolute) {
    
    // Create test values
    uint8_t opCode = 0x8E;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t xTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->registers.X = xTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check address has been set to X Register value
    EXPECT_EQ(cpu->mem[addr],xTestVal);
  
}
