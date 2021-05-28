#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_LSR : public testing::Test
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

TEST_F(Core6502Tests_LSR, LSR_ACCUMULATOR_INIT_NEG) {

	// Create test values
 	uint8_t opCode = 0x4A;
	uint8_t testVal = 0x80;

	// Set registers
	cpu->registers.A = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->registers.A, testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal >> 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}
TEST_F(Core6502Tests_LSR, LSR_ACCUMULATOR_END_ZERO) {

	// Create test values
 	uint8_t opCode = 0x4A;
	uint8_t testVal = 0x01;

	// Set registers
	cpu->registers.A = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->registers.A, testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal >> 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}
TEST_F(Core6502Tests_LSR, LSR_ACCUMULATOR_INIT_ZERO) {

	// Create test values
 	uint8_t opCode = 0x4A;
	uint8_t testVal = 0x00;

	// Set registers
	cpu->registers.A = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->registers.A, 0);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}

TEST_F(Core6502Tests_LSR, LSR_ZERO_PAGE_INIT_NEG) {

	// Create test values
 	uint8_t opCode = 0x46;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 0x40;
	uint8_t testVal = 0x80;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal >> 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}
TEST_F(Core6502Tests_LSR, LSR_ZERO_PAGE_END_ZERO) {

	// Create test values
 	uint8_t opCode = 0x46;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 040;
	uint8_t testVal = 0x01;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal >> 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}
TEST_F(Core6502Tests_LSR, LSR_ZERO_PAGE_INIT_ZERO) {

	// Create test values
 	uint8_t opCode = 0x46;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 040;
	uint8_t testVal = 0x00;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}

TEST_F(Core6502Tests_LSR, LSR_ZERO_PAGE_X_INIT_NEG) {

	// Create test values
 	uint8_t opCode = 0x56;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 0x40;
	uint8_t xVal = 0x10;
	uint8_t testVal = 0x80;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal >> 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}
TEST_F(Core6502Tests_LSR, LSR_ZERO_PAGE_X_END_ZERO) {

	// Create test values
 	uint8_t opCode = 0x56;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 040;
	uint8_t xVal = 0x10;
	uint8_t testVal = 0x01;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal >> 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}
TEST_F(Core6502Tests_LSR, LSR_ZERO_PAGE_X_INIT_ZERO) {

	// Create test values
 	uint8_t opCode = 0x56;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 040;
	uint8_t xVal = 0x10;
	uint8_t testVal = 0x00;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}

TEST_F(Core6502Tests_LSR, LSR_ABSOLUTE_INIT_NEG) {

	// Create test values
 	uint8_t opCode = 0x4E;
	uint16_t pcVal = 0x4000;
	uint8_t addrLB = 0xFE;
	uint8_t addrUB = 0xCA;
	uint16_t addr = (addrUB << 8) + addrLB;
	uint8_t testVal = 0x80;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal >> 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}
TEST_F(Core6502Tests_LSR, LSR_ABSOLUTE_END_ZERO) {

	// Create test values
 	uint8_t opCode = 0x4E;
	uint16_t pcVal = 0x4000;
	uint8_t addrLB = 0xFE;
	uint8_t addrUB = 0xCA;
	uint16_t addr = (addrUB << 8) + addrLB;
	uint8_t testVal = 0x1;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr] = testVal;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal >> 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}
TEST_F(Core6502Tests_LSR, LSR_ABSOLUTE_INIT_ZERO) {

	// Create test values
 	uint8_t opCode = 0x4E;
	uint16_t pcVal = 0x4000;
	uint8_t addrLB = 0xFE;
	uint8_t addrUB = 0xCA;
	uint16_t addr = (addrUB << 8) + addrLB;
	uint8_t testVal = 0x0;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr] = testVal;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}

TEST_F(Core6502Tests_LSR, LSR_ABSOLUTE_X_INIT_NEG) {

	// Create test values
 	uint8_t opCode = 0x5E;
	uint16_t pcVal = 0x4000;
	uint8_t addrLB = 0xFE;
	uint8_t addrUB = 0xCA;
	uint8_t xVal = 0x10;
	uint16_t addr = (addrUB << 8) + addrLB;
	uint8_t testVal = 0x80;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr + xVal] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal >> 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}
TEST_F(Core6502Tests_LSR, LSR_ABSOLUTE_X_END_ZERO) {

	// Create test values
 	uint8_t opCode = 0x5E;
	uint16_t pcVal = 0x4000;
	uint8_t addrLB = 0xFE;
	uint8_t addrUB = 0xCA;
	uint8_t xVal = 0x10;
	uint16_t addr = (addrUB << 8) + addrLB;
	uint8_t testVal = 0x1;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr + xVal] = testVal;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal >> 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}
TEST_F(Core6502Tests_LSR, LSR_ABSOLUTE_X_INIT_ZERO) {

	// Create test values
 	uint8_t opCode = 0x5E;
	uint16_t pcVal = 0x4000;
	uint8_t addrLB = 0xFE;
	uint8_t addrUB = 0xCA;
	uint8_t xVal = 0x10;
	uint16_t addr = (addrUB << 8) + addrLB;
	uint8_t testVal = 0x0;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr + xVal] = testVal;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], testVal >> 1);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, testVal & 0x1);

}

