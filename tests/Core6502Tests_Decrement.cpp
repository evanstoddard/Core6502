#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_Decrement : public testing::Test
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

// DEC Zero Page
TEST_F(Core6502Tests_Decrement, Test_DEC_Zero_Page_Positive) {
    
    // Create test values
    uint8_t opCode = 0xC6;
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
    EXPECT_EQ((uint8_t)cpu->mem[addr], (uint8_t)(testVal - 1));
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Decrement, Test_DEC_Zero_Page_Negative) {
    
    // Create test values
    uint8_t opCode = 0xC6;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t testVal = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ((uint8_t)cpu->mem[addr], (uint8_t)(testVal - 1));
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Decrement, Test_DEC_Zero_Page_Zero) {
    
    // Create test values
    uint8_t opCode = 0xC6;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t testVal = 0x01;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ((uint8_t)cpu->mem[addr], 0);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}

// DEC Zero Page X
TEST_F(Core6502Tests_Decrement, Test_DEC_Zero_Page_X_Positive) {
    
    // Create test values
    uint8_t opCode = 0xD6;
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
    EXPECT_EQ((uint8_t)cpu->mem[addr + xVal], (uint8_t)(testVal - 1));
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Decrement, Test_DEC_Zero_Page_X_Negative) {
    
    // Create test values
    uint8_t opCode = 0xD6;
    uint16_t pcVal = 0x4000;
    uint8_t xVal = 0x10;
    uint8_t addr = 0x40;
    uint8_t testVal = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr + xVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ((uint8_t)cpu->mem[addr + xVal], (uint8_t)(testVal - 1));
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Decrement, Test_DEC_Zero_Page_X_Zero) {
    
    // Create test values
    uint8_t opCode = 0xD6;
    uint16_t pcVal = 0x4000;
    uint8_t xVal = 0x10;
    uint8_t addr = 0x40;
    uint8_t testVal = 0x01;

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

// DEC Absolute
TEST_F(Core6502Tests_Decrement, Test_DEC_Absolute_Positive) {
    
    // Create test values
    uint8_t opCode = 0xCE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xCA;
    uint8_t absoluteLB = 0xDE;
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
    EXPECT_EQ((uint8_t)cpu->mem[addr], (uint8_t)(testVal - 1));
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Decrement, Test_DEC_Absolute_Negative) {
    
    // Create test values
    uint8_t opCode = 0xCE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xCA;
    uint8_t absoluteLB = 0xDE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t testVal = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal + 1] = absoluteUB;
    cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ((uint8_t)cpu->mem[addr], (uint8_t)(testVal - 1));
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Decrement, Test_DEC_Absolute_Zero) {
    
    // Create test values
    uint8_t opCode = 0xCE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xCA;
    uint8_t absoluteLB = 0xDE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t testVal = 0x01;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal + 1] = absoluteUB;
    cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ((uint8_t)cpu->mem[addr], 0);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}

// DEC Absolute X
TEST_F(Core6502Tests_Decrement, Test_DEC_Absolute_X_Positive) {
    
    // Create test values
    uint8_t opCode = 0xDE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xCA;
    uint8_t absoluteLB = 0xDE;
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
    EXPECT_EQ((uint8_t)cpu->mem[addr + xVal], (uint8_t)(testVal - 1));
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Decrement, Test_DEC_Absolute_X_Negative) {
    
    // Create test values
    uint8_t opCode = 0xDE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xBE;
    uint8_t absoluteLB = 0xEF;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t xVal = 0x10;
    uint8_t testVal = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal + 1] = absoluteUB;
    cpu->mem[addr + xVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ((uint8_t)cpu->mem[addr + xVal], (uint8_t)(testVal - 1));
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Decrement, Test_DEC_Absolute_X_Zero) {
    
    // Create test values
    uint8_t opCode = 0xDE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xCA;
    uint8_t absoluteLB = 0xDE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t xVal = 0x10;
    uint8_t testVal = 0x01;

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

// DEX  
TEST_F(Core6502Tests_Decrement, Test_DEX_Positive) {
    
    // Create test values
    uint8_t opCode = 0xCA;
    uint16_t pcVal = 0x4000;
    uint8_t testVal = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.X, (uint8_t)(testVal - 1));
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Decrement, Test_DEX_Negative) {
    
    // Create test values
    uint8_t opCode = 0xCA;
    uint16_t pcVal = 0x4000;
    uint8_t testVal = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.X, (uint8_t)(testVal - 1));
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Decrement, Test_DEX_Zero) {
    
    // Create test values
    uint8_t opCode = 0xCA;
    uint16_t pcVal = 0x4000;
    uint8_t testVal = 0x01;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.X, 0);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}

// DEXY 
TEST_F(Core6502Tests_Decrement, Test_DEY_Positive) {
    
    // Create test values
    uint8_t opCode = 0x88;
    uint16_t pcVal = 0x4000;
    uint8_t testVal = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.Y, (uint8_t)(testVal - 1));
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Decrement, Test_DEY_Negative) {
    
    // Create test values
    uint8_t opCode = 0x88;
    uint16_t pcVal = 0x4000;
    uint8_t testVal = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.Y, (uint8_t)(testVal - 1));
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_Decrement, Test_DEY_Zero) {
    
    // Create test values
    uint8_t opCode = 0x88;
    uint16_t pcVal = 0x4000;
    uint8_t testVal = 0x01;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.Y, 0);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}
