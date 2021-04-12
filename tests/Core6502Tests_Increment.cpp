#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_Increment : public testing::Test
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

// INC Zero Page
TEST_F(Core6502Tests_Increment, Test_INC_Zero_Page_Positive) {
    
    // Create test values
    uint8_t opCode = 0xE6;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t testVal = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->mem[addr], testVal + 1);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Increment, Test_INC_Zero_Page_Negative) {
    
    // Create test values
    uint8_t opCode = 0xE6;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t testVal = 0x7F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->mem[addr], testVal + 1);
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Increment, Test_INC_Zero_Page_Zero) {
    
    // Create test values
    uint8_t opCode = 0xE6;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t testVal = 0xFF;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->mem[addr], 0);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}

// INC Zero Page X
TEST_F(Core6502Tests_Increment, Test_INC_Zero_Page_X_Positive) {
    
    // Create test values
    uint8_t opCode = 0xF6;
    uint16_t pcVal = 0x4000;
    uint8_t xVal = 0x10;
    uint8_t addr = 0x40;
    uint8_t testVal = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr + xVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->mem[addr + xVal], testVal + 1);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Increment, Test_INC_Zero_Page_X_Negative) {
    
    // Create test values
    uint8_t opCode = 0xF6;
    uint16_t pcVal = 0x4000;
    uint8_t xVal = 0x10;
    uint8_t addr = 0x40;
    uint8_t testVal = 0x7F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr + xVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->mem[addr + xVal], testVal + 1);
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Increment, Test_INC_Zero_Page_X_Zero) {
    
    // Create test values
    uint8_t opCode = 0xF6;
    uint16_t pcVal = 0x4000;
    uint8_t xVal = 0x10;
    uint8_t addr = 0x40;
    uint8_t testVal = 0xFF;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr + xVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->mem[addr + xVal], 0);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}

// INC Absolute
TEST_F(Core6502Tests_Increment, Test_INC_Absolute_Positive) {
    
    // Create test values
    uint8_t opCode = 0xEE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xCA;
    uint8_t absoluteLB = 0xFE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t testVal = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal + 1] = absoluteUB;
    cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->mem[addr], testVal + 1);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Increment, Test_INC_Absolute_Negative) {
    
    // Create test values
    uint8_t opCode = 0xEE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xCA;
    uint8_t absoluteLB = 0xFE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t testVal = 0x7F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal + 1] = absoluteUB;
    cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->mem[addr], testVal + 1);
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Increment, Test_INC_Absolute_Zero) {
    
    // Create test values
    uint8_t opCode = 0xEE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xCA;
    uint8_t absoluteLB = 0xFE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t testVal = 0xFF;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal + 1] = absoluteUB;
    cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->mem[addr], 0);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}

// INC Absolute X
TEST_F(Core6502Tests_Increment, Test_INC_Absolute_X_Positive) {
    
    // Create test values
    uint8_t opCode = 0xFE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xCA;
    uint8_t absoluteLB = 0xFE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t xVal = 0x10;
    uint8_t testVal = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal + 1] = absoluteUB;
    cpu->mem[addr + xVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->mem[addr + xVal], testVal + 1);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Increment, Test_INC_Absolute_X_Negative) {
    
    // Create test values
    uint8_t opCode = 0xFE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xBE;
    uint8_t absoluteLB = 0xEF;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t xVal = 0x10;
    uint8_t testVal = 0x7F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal + 1] = absoluteUB;
    cpu->mem[addr + xVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->mem[addr + xVal], testVal + 1);
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Increment, Test_INC_Absolute_X_Zero) {
    
    // Create test values
    uint8_t opCode = 0xFE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xCA;
    uint8_t absoluteLB = 0xFE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t xVal = 0x10;
    uint8_t testVal = 0xFF;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal + 1] = absoluteUB;
    cpu->mem[addr + xVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->mem[addr + xVal], 0);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}
