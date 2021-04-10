#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_Transfer : public testing::Test
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

TEST_F(Core6502Tests_Transfer, TAX_Positive) {
    
    // Create test values
    uint8_t opCode = 0xAA;
    uint8_t testVal = 0x0A;
    
    // Set Registers
    cpu->registers.A = testVal;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(testVal, cpu->registers.X);
    EXPECT_EQ((testVal == 0), cpu->status.ZeroFlag);
    EXPECT_EQ((bool)(testVal & 0b10000000), cpu->status.NegativeFlag);
    
}
TEST_F(Core6502Tests_Transfer, TAX_Negative) {
    
    // Create test values
    uint8_t opCode = 0xAA;
    uint8_t testVal = 0x80;
    
    // Set Registers
    cpu->registers.A = testVal;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(testVal, cpu->registers.X);
    EXPECT_EQ((testVal == 0), cpu->status.ZeroFlag);
    EXPECT_EQ((bool)(testVal & 0b10000000), cpu->status.NegativeFlag);
    
}
TEST_F(Core6502Tests_Transfer, TAX_Zero) {
    
    // Create test values
    uint8_t opCode = 0xAA;
    uint8_t testVal = 0x0;
    
    // Set Registers
    cpu->registers.A = testVal;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(testVal, cpu->registers.X);
    EXPECT_EQ((testVal == 0), cpu->status.ZeroFlag);
    EXPECT_EQ((bool)(testVal & 0b10000000), cpu->status.NegativeFlag);
    
}

TEST_F(Core6502Tests_Transfer, TAY_Positive) {
    
    // Create test values
    uint8_t opCode = 0xA8;
    uint8_t testVal = 0x0A;
    
    // Set Registers
    cpu->registers.A = testVal;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(testVal, cpu->registers.Y);
    EXPECT_EQ((testVal == 0), cpu->status.ZeroFlag);
    EXPECT_EQ((bool)(testVal & 0b10000000), cpu->status.NegativeFlag);
    
}
TEST_F(Core6502Tests_Transfer, TAY_Negative) {
    
    // Create test values
    uint8_t opCode = 0xA8;
    uint8_t testVal = 0x80;
    
    // Set Registers
    cpu->registers.A = testVal;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(testVal, cpu->registers.Y);
    EXPECT_EQ((testVal == 0), cpu->status.ZeroFlag);
    EXPECT_EQ((bool)(testVal & 0b10000000), cpu->status.NegativeFlag);
    
}
TEST_F(Core6502Tests_Transfer, TAY_Zero) {
    
    // Create test values
    uint8_t opCode = 0xA8;
    uint8_t testVal = 0x0;
    
    // Set Registers
    cpu->registers.A = testVal;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(testVal, cpu->registers.Y);
    EXPECT_EQ((testVal == 0), cpu->status.ZeroFlag);
    EXPECT_EQ((bool)(testVal & 0b10000000), cpu->status.NegativeFlag);
    
}

TEST_F(Core6502Tests_Transfer, TXA_Positive) {
    
    // Create test values
    uint8_t opCode = 0x8A;
    uint8_t testVal = 0x0A;
    
    // Set Registers
    cpu->registers.X = testVal;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(testVal, cpu->registers.A);
    EXPECT_EQ((testVal == 0), cpu->status.ZeroFlag);
    EXPECT_EQ((bool)(testVal & 0b10000000), cpu->status.NegativeFlag);
    
}
TEST_F(Core6502Tests_Transfer, TXA_Negative) {
    
    // Create test values
    uint8_t opCode = 0x8A;
    uint8_t testVal = 0x80;
    
    // Set Registers
    cpu->registers.X = testVal;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(testVal, cpu->registers.A);
    EXPECT_EQ((testVal == 0), cpu->status.ZeroFlag);
    EXPECT_EQ((bool)(testVal & 0b10000000), cpu->status.NegativeFlag);
    
}
TEST_F(Core6502Tests_Transfer, TXA_Zero) {
    
    // Create test values
    uint8_t opCode = 0x8A;
    uint8_t testVal = 0x0;
    
    // Set Registers
    cpu->registers.X = testVal;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(testVal, cpu->registers.A);
    EXPECT_EQ((testVal == 0), cpu->status.ZeroFlag);
    EXPECT_EQ((bool)(testVal & 0b10000000), cpu->status.NegativeFlag);
    
}

TEST_F(Core6502Tests_Transfer, TYA_Positive) {
    
    // Create test values
    uint8_t opCode = 0x98;
    uint8_t testVal = 0x0A;
    
    // Set Registers
    cpu->registers.Y = testVal;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(testVal, cpu->registers.A);
    EXPECT_EQ((testVal == 0), cpu->status.ZeroFlag);
    EXPECT_EQ((bool)(testVal & 0b10000000), cpu->status.NegativeFlag);
    
}
TEST_F(Core6502Tests_Transfer, TYA_Negative) {
    
    // Create test values
    uint8_t opCode = 0x98;
    uint8_t testVal = 0x80;
    
    // Set Registers
    cpu->registers.Y = testVal;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(testVal, cpu->registers.A);
    EXPECT_EQ((testVal == 0), cpu->status.ZeroFlag);
    EXPECT_EQ((bool)(testVal & 0b10000000), cpu->status.NegativeFlag);
    
}
TEST_F(Core6502Tests_Transfer, TYA_Zero) {
    
    // Create test values
    uint8_t opCode = 0x98;
    uint8_t testVal = 0x0;
    
    // Set Registers
    cpu->registers.Y = testVal;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(testVal, cpu->registers.A);
    EXPECT_EQ((testVal == 0), cpu->status.ZeroFlag);
    EXPECT_EQ((bool)(testVal & 0b10000000), cpu->status.NegativeFlag);
    
}
