#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_CMP : public testing::Test
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


TEST_F(Core6502Tests_CMP, CMP_IMMEDIATE_A_GREATER) {
    
    // Create test values
    uint8_t opCode = 0xC9;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x10;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CMP, CMP_IMMEDIATE_A_EQUAL) {
    
    // Create test values
    uint8_t opCode = 0xC9;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x20;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CMP, CMP_IMMEDIATE_A_NEGATIVE) {
    
    // Create test values
    uint8_t opCode = 0xC9;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x21;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}

TEST_F(Core6502Tests_CMP, CMP_ZERO_PAGE_A_GREATER) {
    
    // Create test values
    uint8_t opCode = 0xC5;
    uint16_t pcVal = 0x4000;
	uint8_t zeroPageAddr = 0x40;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x10;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = zeroPageAddr;
	cpu->mem[zeroPageAddr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CMP, CMP_ZERO_PAGE_A_EQUAL) {
    
    // Create test values
    uint8_t opCode = 0xC5;
    uint16_t pcVal = 0x4000;
	uint8_t zeroPageAddr = 0x40;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x20;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = zeroPageAddr;
	cpu->mem[zeroPageAddr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CMP, CMP_ZERO_PAGE_A_NEGATIVE) {
    
    // Create test values
    uint8_t opCode = 0xC5;
    uint16_t pcVal = 0x4000;
	uint8_t zeroPageAddr = 0x40;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x21;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = zeroPageAddr;
	cpu->mem[zeroPageAddr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}

TEST_F(Core6502Tests_CMP, CMP_ZERO_PAGE_X_A_GREATER) {
    
    // Create test values
    uint8_t opCode = 0xD5;
    uint16_t pcVal = 0x4000;
	uint8_t zeroPageAddr = 0x40;
	uint8_t xVal	= 0x10;
	uint8_t addr 	= zeroPageAddr + xVal;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x10;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
	cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
	cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CMP, CMP_ZERO_PAGE_X_A_EQUAL) {
    
    // Create test values
    uint8_t opCode = 0xD5;
    uint16_t pcVal = 0x4000;
	uint8_t xVal	= 0x10;
	uint8_t zeroPageAddr = 0x40;
	uint8_t addr 	= zeroPageAddr + xVal;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x20;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
	cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
	cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CMP, CMP_ZERO_PAGE_X_A_NEGATIVE) {
    
    // Create test values
    uint8_t opCode = 0xD5;
    uint16_t pcVal = 0x4000;
	uint8_t zeroPageAddr = 0x40;
	uint8_t xVal	= 0x10;
	uint8_t addr 	= zeroPageAddr + xVal;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x21;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
	cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
	cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}

TEST_F(Core6502Tests_CMP, CMP_ABSOLUTE_A_GREATER) {
    
    // Create test values
    uint8_t opCode = 0xCD;
    uint16_t pcVal = 0x4000;
	uint8_t addrUpper = 0xCA;
	uint8_t addrLower = 0xFE;
	uint16_t addr = (addrUpper << 8) + addrLower;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x10;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = addrLower;
	cpu->mem[pcVal + 1] = addrUpper;
	cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CMP, CMP_ABSOLUTE_A_EQUAL) {
    
    // Create test values
    uint8_t opCode = 0xCD;
    uint16_t pcVal = 0x4000;
	uint8_t addrUpper = 0xCA;
	uint8_t addrLower = 0xFE;
	uint16_t addr = (addrUpper << 8) + addrLower;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x20;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = addrLower;
	cpu->mem[pcVal + 1] = addrUpper;
	cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CMP, CMP_ABSOLUTE_A_NEGATIVE) {
    
    // Create test values
    uint8_t opCode = 0xCD;
    uint16_t pcVal = 0x4000;
	uint8_t addrUpper = 0xCA;
	uint8_t addrLower = 0xFE;
	uint16_t addr = (addrUpper << 8) + addrLower;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x21;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = addrLower;
	cpu->mem[pcVal + 1] = addrUpper;
	cpu->mem[addr] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}

TEST_F(Core6502Tests_CMP, CMP_ABSOLUTE_X_A_GREATER) {
    
    // Create test values
    uint8_t opCode = 0xDD;
    uint16_t pcVal = 0x4000;
	uint8_t xVal = 0x20;
	uint8_t addrUpper = 0xCA;
	uint8_t addrLower = 0xFE;
	uint16_t addr = (addrUpper << 8) + addrLower;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x10;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
	cpu->registers.X = xVal;
    cpu->mem[pcVal] = addrLower;
	cpu->mem[pcVal + 1] = addrUpper;
	cpu->mem[addr + xVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CMP, CMP_ABSOLUTE_X_A_EQUAL) {
    
    // Create test values
    uint8_t opCode = 0xDD;
    uint16_t pcVal = 0x4000;
	uint8_t xVal = 0x20;
	uint8_t addrUpper = 0xCA;
	uint8_t addrLower = 0xFE;
	uint16_t addr = (addrUpper << 8) + addrLower;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x20;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
	cpu->registers.X = xVal;
    cpu->mem[pcVal] = addrLower;
	cpu->mem[pcVal + 1] = addrUpper;
	cpu->mem[addr + xVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CMP, CMP_ABSOLUTE_X_A_NEGATIVE) {
    
    // Create test values
    uint8_t opCode = 0xDD;
    uint16_t pcVal = 0x4000;
	uint8_t xVal = 0x20;
	uint8_t addrUpper = 0xCA;
	uint8_t addrLower = 0xFE;
	uint16_t addr = (addrUpper << 8) + addrLower;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x21;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
	cpu->registers.X = xVal;
    cpu->mem[pcVal] = addrLower;
	cpu->mem[pcVal + 1] = addrUpper;
	cpu->mem[addr + xVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}

TEST_F(Core6502Tests_CMP, CMP_ABSOLUTE_Y_A_GREATER) {
    
    // Create test values
    uint8_t opCode = 0xD9;
    uint16_t pcVal = 0x4000;
	uint8_t yVal = 0x20;
	uint8_t addrUpper = 0xCA;
	uint8_t addrLower = 0xFE;
	uint16_t addr = (addrUpper << 8) + addrLower;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x10;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
	cpu->registers.Y = yVal;
    cpu->mem[pcVal] = addrLower;
	cpu->mem[pcVal + 1] = addrUpper;
	cpu->mem[addr + yVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CMP, CMP_ABSOLUTE_Y_A_EQUAL) {
    
    // Create test values
    uint8_t opCode = 0xD9;
    uint16_t pcVal = 0x4000;
	uint8_t yVal = 0x20;
	uint8_t addrUpper = 0xCA;
	uint8_t addrLower = 0xFE;
	uint16_t addr = (addrUpper << 8) + addrLower;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x20;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
	cpu->registers.Y = yVal;
    cpu->mem[pcVal] = addrLower;
	cpu->mem[pcVal + 1] = addrUpper;
	cpu->mem[addr + yVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
TEST_F(Core6502Tests_CMP, CMP_ABSOLUTE_Y_A_NEGATIVE) {
    
    // Create test values
    uint8_t opCode = 0xD9;
    uint16_t pcVal = 0x4000;
	uint8_t yVal = 0x20;
	uint8_t addrUpper = 0xCA;
	uint8_t addrLower = 0xFE;
	uint16_t addr = (addrUpper << 8) + addrLower;
    uint8_t aTestVal = 0x20;
    uint8_t testVal  = 0x21;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
	cpu->registers.Y = yVal;
    cpu->mem[pcVal] = addrLower;
	cpu->mem[pcVal + 1] = addrUpper;
	cpu->mem[addr + yVal] = testVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, aTestVal >= testVal);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(aTestVal - testVal));
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((aTestVal - testVal) & 0x80));

}
