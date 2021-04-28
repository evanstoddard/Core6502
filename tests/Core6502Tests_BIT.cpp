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
    uint8_t opCode = 0x24;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0x0F;
    uint8_t mask = 0x0C;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 0);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Zero_Page_Zero) {
    
    // Create test values
    uint8_t opCode = 0x24;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0x0F;
    uint8_t mask = 0x00;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 0);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Zero_Set_Overflow) {
    
    // Create test values
    uint8_t opCode = 0x24;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0x0F;
    uint8_t mask = 0b01000000;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 1);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Zero_Clear_Overflow) {
    
    // Create test values
    uint8_t opCode = 0x24;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0x0F;
    uint8_t mask = 0b00100000;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 0);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Zero_Set_Negative) {
    
    // Create test values
    uint8_t opCode = 0x24;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0x0F;
    uint8_t mask = 0b10000000;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 0);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Zero_Clear_Negative) {
    
    // Create test values
    uint8_t opCode = 0x24;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0x0F;
    uint8_t mask = 0b00010000;

    // Set Registers BIT memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 0);

}

// BIT Absolute
TEST_F(Core6502Tests_BIT, Test_BIT_Absolute_NonZero) {
    
    // Create test values
    uint8_t opCode = 0x2C;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0x0C;
    uint8_t mask = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 0);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Absolute_Page_Zero) {
    
    // Create test values
    uint8_t opCode = 0x2C;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 0);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Absolute_Set_Overflow) {
    
    // Create test values
    uint8_t opCode = 0x2C;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0x00;
    uint8_t mask = 0b01000000;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 1);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Absolute_Clear_Overflow) {
    
     // Create test values
    uint8_t opCode = 0x2c;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0x00;
    uint8_t mask = 0b00100000;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 0);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Absolute_Set_Negative) {
    
    // Create test values
    uint8_t opCode = 0x2C;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0x00;
    uint8_t mask = 0b10000000;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 0);

}
TEST_F(Core6502Tests_BIT, Test_BIT_Absolute_Clear_Negative) {
    
    // Create test values
    uint8_t opCode = 0x2C;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0x00;
    uint8_t mask = 0b00100000;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 0);

}

