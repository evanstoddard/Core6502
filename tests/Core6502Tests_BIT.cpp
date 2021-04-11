#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_BIT : public testing::Test
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

// BIT Zero Page
TEST_F(Core6502Tests_BIT, Test_BIT_Zero_Page_NonZero) {
    
    // Create test values
    uint8_t opCode = 0x25;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x0F;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Zero_Page_Zero) {
    
    // Create test values
    uint8_t opCode = 0x25;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x00;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Zero_Page_Overflow_Set) {
    
    // Create test values
    uint8_t opCode = 0x25;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x40;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.OverflowFlag, 1);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Zero_Page_Overflow_Clear) {
    
    // Create test values
    uint8_t opCode = 0x25;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x30;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.OverflowFlag, 1);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Zero_Page_Negative_Set) {
    
    // Create test values
    uint8_t opCode = 0x25;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x80;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.NegativeFlag, 1);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Zero_Page_Negative_Clear) {
    
    // Create test values
    uint8_t opCode = 0x25;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x70;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.NegativeFlag, 1);

}


// BIT Absolute
TEST_F(Core6502Tests_BIT, Test_BIT_Absolute_NonZero) {
    
    // Create test values
    uint8_t opCode = 0x2D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x0F;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Absolute_Zero) {
    
    // Create test values
   uint8_t opCode = 0x2D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x00;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Absolute_Overflow_Set) {
    
    // Create test values
    uint8_t opCode = 0x2D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0b01000000;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.OverflowFlag, 1);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Absolute_Overflow_Clear) {
    
    // Create test values
   uint8_t opCode = 0x2D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0b00100000;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.OverflowFlag, 0);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Absolute_Negative_Set) {
    
    // Create test values
    uint8_t opCode = 0x2D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x80;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.NegativeFlag, 1);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Absolute_Negative_Clear) {
    
    // Create test values
   uint8_t opCode = 0x2D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x70;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.NegativeFlag, 0);

}
