#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_STA : public testing::Test
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

// Checks all STA instructions

// STA Zero Page
TEST_F(Core6502Tests_STA, Test_STA_Zero_Page) {
    
    // Create test values
    uint8_t opCode = 0x85;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check address has been set to accumulator value
    EXPECT_EQ(cpu->mem[addr],aTestVal);

}

// STA Zero Page X
TEST_F(Core6502Tests_STA, Test_STA_Zero_Page_X) {
    
    // Create test values
    uint8_t opCode = 0x95;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t xVal = 0x10;
    uint8_t addr = zeroPageAddr + xVal;
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check address has been set to accumulator value
    EXPECT_EQ(cpu->mem[addr],aTestVal);

}

// STA Absolute
TEST_F(Core6502Tests_STA, Test_STA_Absolute) {
    
    // Create test values
    uint8_t opCode = 0x8D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check address has been set to accumulator value
    EXPECT_EQ(cpu->mem[addr],aTestVal);
    
    

    
}

// STA Absolute X
TEST_F(Core6502Tests_STA, Test_STA_Absolute_X) {
    
    // Create test values
    uint8_t opCode = 0x9D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t xVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + xVal;
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check address has been set to accumulator value
    EXPECT_EQ(cpu->mem[addr],aTestVal);
    
    

    
}

// STA Absolute Y
TEST_F(Core6502Tests_STA, Test_STA_Absolute_Y) {
    
    // Create test values
    uint8_t opCode = 0x99;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t yVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + yVal;
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check address has been set to accumulator value
    EXPECT_EQ(cpu->mem[addr],aTestVal);

}
