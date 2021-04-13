#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_Branch : public testing::Test
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

// BCC Tests
TEST_F(Core6502Tests_Branch, Test_BCC_True_Positive_Positive) {
	// Test Values
	uint8_t opCode = 0x90;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.CarryFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, (pcVal + 1 + offset));
}
TEST_F(Core6502Tests_Branch, Test_BCC_True_Positive_Negative) {
	// Test Values
	uint8_t opCode = 0x90;
	uint16_t pcVal = 0x4000;
    int8_t offset = -0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.CarryFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BCC_True_Negative_Positive) {
	// Test Values
	uint8_t opCode = 0x90;
	uint16_t pcVal = 0x8000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.CarryFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BCC_True_Negative_Negative) {
	// Test Values
	uint8_t opCode = 0x90;
	uint16_t pcVal = 0x8000;
    int8_t offset = -0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.CarryFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BCC_False) {
	// Test Values
	uint8_t opCode = 0x90;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.CarryFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1);
}

// BCS Tests
TEST_F(Core6502Tests_Branch, Test_BCS_True_Positive_Positive) {
	// Test Values
	uint8_t opCode = 0xB0;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.CarryFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BCS_True_Positive_Negative) {
	// Test Values
	uint8_t opCode = 0xB0;
	uint16_t pcVal = 0x4000;
    int8_t offset = -0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.CarryFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BCS_True_Negative_Positive) {
	// Test Values
	uint8_t opCode = 0xB0;
	uint16_t pcVal = 0x8000;
    int8_t offset = 0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.CarryFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BCS_True_Negative_Negative) {
	// Test Values
	uint8_t opCode = 0xB0;
	uint16_t pcVal = 0x8000;
    int8_t offset = -0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.CarryFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BCS_False) {
	// Test Values
	uint8_t opCode = 0xB0;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.CarryFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal+1);
}

// BEQ Tests
TEST_F(Core6502Tests_Branch, Test_BEQ_True_Positive_Positive) {
	// Test Values
	uint8_t opCode = 0xF0;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.ZeroFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BEQ_True_Positive_Negative) {
	// Test Values
	uint8_t opCode = 0xF0;
	uint16_t pcVal = 0x4000;
    int8_t offset = -0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.ZeroFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BEQ_True_Negative_Positive) {
	// Test Values
	uint8_t opCode = 0xF0;
	uint16_t pcVal = 0x8000;
    int8_t offset = 0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.ZeroFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BEQ_True_Negative_Negative) {
	// Test Values
	uint8_t opCode = 0xF0;
	uint16_t pcVal = 0x8000;
    int8_t offset = -0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.ZeroFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BEQ_False) {
	// Test Values
	uint8_t opCode = 0xF0;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.ZeroFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1);
}

// BNE Tests
TEST_F(Core6502Tests_Branch, Test_BNE_True_Positive_Positive) {
	// Test Values
	uint8_t opCode = 0xD0;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.ZeroFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BNE_True_Positive_Negative) {
	// Test Values
	uint8_t opCode = 0xD0;
	uint16_t pcVal = 0x4000;
    int8_t offset = -0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.ZeroFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BNE_True_Negative_Positive) {
	// Test Values
	uint8_t opCode = 0xD0;
	uint16_t pcVal = 0x8000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.ZeroFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BNE_True_Negative_Negative) {
	// Test Values
	uint8_t opCode = 0xD0;
	uint16_t pcVal = 0x8000;
    int8_t offset = -0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.ZeroFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BNE_False) {
	// Test Values
	uint8_t opCode = 0xD0;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.ZeroFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1);
}

// BPL Tests
TEST_F(Core6502Tests_Branch, Test_BPL_True_Positive_Positive) {
	// Test Values
	uint8_t opCode = 0x10;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.NegativeFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BPL_True_Positive_Negative) {
	// Test Values
	uint8_t opCode = 0x10;
	uint16_t pcVal = 0x4000;
    int8_t offset = -0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.NegativeFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BPL_True_Negative_Positive) {
	// Test Values
	uint8_t opCode = 0x10;
	uint16_t pcVal = 0x8000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.NegativeFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BPL_True_Negative_Negative) {
	// Test Values
	uint8_t opCode = 0x10;
	uint16_t pcVal = 0x8000;
    int8_t offset = -0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.NegativeFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BPL_False) {
	// Test Values
	uint8_t opCode = 0x10;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.NegativeFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1);
}

// BMI Tests
TEST_F(Core6502Tests_Branch, Test_BMI_True_Positive_Positive) {
	// Test Values
	uint8_t opCode = 0x30;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.NegativeFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BMI_True_Positive_Negative) {
	// Test Values
	uint8_t opCode = 0x30;
	uint16_t pcVal = 0x4000;
    int8_t offset = -0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.NegativeFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BMI_True_Negative_Positive) {
	// Test Values
	uint8_t opCode = 0x30;
	uint16_t pcVal = 0x8000;
    int8_t offset = 0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.NegativeFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BMI_True_Negative_Negative) {
	// Test Values
	uint8_t opCode = 0x30;
	uint16_t pcVal = 0x8000;
    int8_t offset = -0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.NegativeFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BMI_False) {
	// Test Values
	uint8_t opCode = 0x30;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.NegativeFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1);
}

// BVC Tests
TEST_F(Core6502Tests_Branch, Test_BVC_True_Positive_Positive) {
	// Test Values
	uint8_t opCode = 0x50;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.OverflowFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BVC_True_Positive_Negative) {
	// Test Values
	uint8_t opCode = 0x50;
	uint16_t pcVal = 0x4000;
    int8_t offset = -0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.OverflowFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BVC_True_Negative_Positive) {
	// Test Values
	uint8_t opCode = 0x50;
	uint16_t pcVal = 0x8000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.OverflowFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BVC_True_Negative_Negative) {
	// Test Values
	uint8_t opCode = 0x50;
	uint16_t pcVal = 0x8000;
    int8_t offset = -0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.OverflowFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BVC_False) {
	// Test Values
	uint8_t opCode = 0x50;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.OverflowFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1);
}

// BVS Tests
TEST_F(Core6502Tests_Branch, Test_BVS_True_Positive_Positive) {
	// Test Values
	uint8_t opCode = 0x70;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.OverflowFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BVS_True_Positive_Negative) {
	// Test Values
	uint8_t opCode = 0x70;
	uint16_t pcVal = 0x4000;
    int8_t offset = -0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.OverflowFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BVS_True_Negative_Positive) {
	// Test Values
	uint8_t opCode = 0x70;
	uint16_t pcVal = 0x8000;
    int8_t offset = 0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.OverflowFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BVS_True_Negative_Negative) {
	// Test Values
	uint8_t opCode = 0x70;
	uint16_t pcVal = 0x8000;
    int8_t offset = -0x40;
	uint8_t flag = 0x1;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.OverflowFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1 + offset);
}
TEST_F(Core6502Tests_Branch, Test_BVS_False) {
	// Test Values
	uint8_t opCode = 0x70;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = offset;
	cpu->status.OverflowFlag = flag;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test cases
	EXPECT_EQ(cpu->registers.PC, pcVal + 1);
}
