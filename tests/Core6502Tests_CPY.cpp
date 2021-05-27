#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_CPY : public testing::Test
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


TEST_F(Core6502Tests_CPY, CPY_IMMEDIATE_Y_GREATER) {
    
    // Create test values
    uint8_t opCode = 0xC0;
    uint16_t pcVal = 0x4000;
    uint8_t yTestVal = 0x20;
    uint8_t testVal  = 0x10;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yTestVal;
    cpu->mem[pcVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, yTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(yTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((yTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CPY, CPY_IMMEDIATE_Y_EQUAL) {
    
    // Create test values
    uint8_t opCode = 0xC0;
    uint16_t pcVal = 0x4000;
    uint8_t yTestVal = 0x20;
    uint8_t testVal  = 0x20;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yTestVal;
    cpu->mem[pcVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, yTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(yTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((yTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CPY, CPY_IMMEDIATE_Y_NEGATIVE) {
    
    // Create test values
    uint8_t opCode = 0xC0;
    uint16_t pcVal = 0x4000;
    uint8_t yTestVal = 0x20;
    uint8_t testVal  = 0x21;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yTestVal;
    cpu->mem[pcVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, yTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(yTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((yTestVal - testVal) & 0x80));

}

TEST_F(Core6502Tests_CPY, CPY_ZERO_PAGE_Y_GREATER) {
    
    // Create test values
    uint8_t opCode = 0xC4;
    uint16_t pcVal = 0x4000;
	uint8_t zeroPageAddr = 0x40;
    uint8_t yTestVal = 0x20;
    uint8_t testVal  = 0x10;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yTestVal;
    cpu->mem[pcVal] = zeroPageAddr;
	cpu->mem[zeroPageAddr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, yTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(yTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((yTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CPY, CPY_ZERO_PAGE_Y_EQUAL) {
    
    // Create test values
    uint8_t opCode = 0xC4;
    uint16_t pcVal = 0x4000;
	uint8_t zeroPageAddr = 0x40;
    uint8_t yTestVal = 0x20;
    uint8_t testVal  = 0x20;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yTestVal;
    cpu->mem[pcVal] = zeroPageAddr;
	cpu->mem[zeroPageAddr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, yTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(yTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((yTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CPY, CPY_ZERO_PAGE_Y_NEGATIVE) {
    
    // Create test values
    uint8_t opCode = 0xC4;
    uint16_t pcVal = 0x4000;
	uint8_t zeroPageAddr = 0x40;
    uint8_t yTestVal = 0x20;
    uint8_t testVal  = 0x21;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yTestVal;
    cpu->mem[pcVal] = zeroPageAddr;
	cpu->mem[zeroPageAddr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, yTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(yTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((yTestVal - testVal) & 0x80));

}

TEST_F(Core6502Tests_CPY, CPY_ABSOLUTE_Y_GREATER) {
    
    // Create test values
    uint8_t opCode = 0xCC;
    uint16_t pcVal = 0x4000;
	uint8_t addrUpper = 0xCA;
	uint8_t addrLower = 0xFE;
	uint16_t addr = (addrUpper << 8) + addrLower;
    uint8_t yTestVal = 0x20;
    uint8_t testVal  = 0x10;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yTestVal;
    cpu->mem[pcVal] = addrLower;
	cpu->mem[pcVal + 1] = addrUpper;
	cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, yTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(yTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((yTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CPY, CPY_ABSOLUTE_Y_EQUAL) {
    
    // Create test values
    uint8_t opCode = 0xCC;
    uint16_t pcVal = 0x4000;
	uint8_t addrUpper = 0xCA;
	uint8_t addrLower = 0xFE;
	uint16_t addr = (addrUpper << 8) + addrLower;
    uint8_t yTestVal = 0x20;
    uint8_t testVal  = 0x20;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yTestVal;
    cpu->mem[pcVal] = addrLower;
	cpu->mem[pcVal + 1] = addrUpper;
	cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, yTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(yTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((yTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CPY, CPY_ABSOLUTE_Y_NEGATIVE) {
    
    // Create test values
    uint8_t opCode = 0xCC;
    uint16_t pcVal = 0x4000;
	uint8_t addrUpper = 0xCA;
	uint8_t addrLower = 0xFE;
	uint16_t addr = (addrUpper << 8) + addrLower;
    uint8_t yTestVal = 0x20;
    uint8_t testVal  = 0x21;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yTestVal;
    cpu->mem[pcVal] = addrLower;
	cpu->mem[pcVal + 1] = addrUpper;
	cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, yTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(yTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((yTestVal - testVal) & 0x80));

}
