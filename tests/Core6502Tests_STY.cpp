#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_STY : public testing::Test
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

// Checks all STY instructions

// STY Zero Page
TEST_F(Core6502Tests_STY, Test_STY_Zero_Page) {
    
    // Create test values
    uint8_t opCode = 0x84;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t yTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->registers.Y = yTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check address has been set to Y Register value
    EXPECT_EQ(cpu->mem[addr],yTestVal);

}

// STY Zero Page Y
TEST_F(Core6502Tests_STY, Test_STY_Zero_Page_X) {
    
    // Create test values
    uint8_t opCode = 0x94;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t xVal = 0x10;
    uint8_t addr = zeroPageAddr + xVal;
    uint8_t yTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->registers.Y = yTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check address has been set to Y Register value
    EXPECT_EQ(cpu->mem[addr],yTestVal);
 
}

// STY Absolute
TEST_F(Core6502Tests_STY, Test_STY_Absolute) {
    
    // Create test values
    uint8_t opCode = 0x8C;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t yTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->registers.Y = yTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check address has been set to Y Register value
    EXPECT_EQ(cpu->mem[addr],yTestVal);
 
}
