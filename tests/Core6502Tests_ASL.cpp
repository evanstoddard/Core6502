#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_ASL : public testing::Test
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

TEST_F(Core6502Tests_ASL, ASL_ACCUMULATOR_NEG) {

	// Create test values
 	uint8_t opCode = 0x0A;
	uint8_t testVal = 0x40;

	// Set registers
	cpu->registers.A = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->registers.A, (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}
TEST_F(Core6502Tests_ASL, ASL_ACCUMULATOR_END_ZERO) {

	// Create test values
 	uint8_t opCode = 0x0A;
	uint8_t testVal = 0x80;

	// Set registers
	cpu->registers.A = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->registers.A, (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}
TEST_F(Core6502Tests_ASL, ASL_ACCUMULATOR_INIT_ZERO) {

	// Create test values
 	uint8_t opCode = 0x0A;
	uint8_t testVal = 0x00;

	// Set registers
	cpu->registers.A = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->registers.A, 0);
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, 0);

}
TEST_F(Core6502Tests_ASL, ASL_ACCUMULATOR) {

	// Create test values
 	uint8_t opCode = 0x0A;
	uint8_t testVal = 0x27;

	// Set registers
	cpu->registers.A = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->registers.A, (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}

TEST_F(Core6502Tests_ASL, ASL_ZERO_PAGE_NEG) {

	// Create test values
 	uint8_t opCode = 0x06;
	uint8_t testVal = 0x40;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 0x40;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}
TEST_F(Core6502Tests_ASL, ASL_ZERO_PAGE_END_ZERO) {

	// Create test values
 	uint8_t opCode = 0x06;
	uint8_t testVal = 0x80;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 0x40;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}
TEST_F(Core6502Tests_ASL, ASL_ZERO_PAGE_INIT_ZERO) {

	// Create test values
 	uint8_t opCode = 0x06;
	uint8_t testVal = 0x00;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 0x40;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, 0);

}
TEST_F(Core6502Tests_ASL, ASL_ZERO_PAGE) {

	// Create test values
 	uint8_t opCode = 0x06;
	uint8_t testVal = 0x27;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 0x40;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}

TEST_F(Core6502Tests_ASL, ASL_ZERO_PAGE_X_NEG) {

	// Create test values
 	uint8_t opCode = 0x16;
	uint8_t testVal = 0x40;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 0x40;
	uint8_t xVal = 0x10;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->registers.X = xVal;
	cpu->mem[addr + xVal] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}
TEST_F(Core6502Tests_ASL, ASL_ZERO_PAGE_X_END_ZERO) {

	// Create test values
 	uint8_t opCode = 0x16;
	uint8_t testVal = 0x80;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 0x40;
	uint8_t xVal = 0x10;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->registers.X = xVal;
	cpu->mem[addr + xVal] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}
TEST_F(Core6502Tests_ASL, ASL_ZERO_PAGE_X_INIT_ZERO) {

	// Create test values
 	uint8_t opCode = 0x16;
	uint8_t testVal = 0x00;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 0x40;
	uint8_t xVal = 0x10;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->registers.X = xVal;
	cpu->mem[addr + xVal] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, 0);

}
TEST_F(Core6502Tests_ASL, ASL_ZERO_PAGE_X) {

	// Create test values
 	uint8_t opCode = 0x16;
	uint8_t testVal = 0x27;
	uint16_t pcVal = 0x4000;
	uint8_t addr = 0x40;
	uint8_t xVal = 0x10;

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->registers.X = xVal;
	cpu->mem[addr + xVal] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}

TEST_F(Core6502Tests_ASL, ASL_ABSOLUTE_NEG) {

	// Create test values
 	uint8_t opCode = 0x0E;
	uint8_t testVal = 0x40;
	uint16_t pcVal = 0x4000;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) + (addrLB);

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}
TEST_F(Core6502Tests_ASL, ASL_ABSOLUTE_END_ZERO) {

	// Create test values
 	uint8_t opCode = 0x0E;
	uint8_t testVal = 0x80;
	uint16_t pcVal = 0x4000;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) + (addrLB);

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}
TEST_F(Core6502Tests_ASL, ASL_ABSOLUTE_INIT_ZERO) {

	// Create test values
 	uint8_t opCode = 0x0E;
	uint8_t testVal = 0x00;
	uint16_t pcVal = 0x4000;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) + (addrLB);

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, 0);

}
TEST_F(Core6502Tests_ASL, ASL_ABSOLUTE) {

	// Create test values
 	uint8_t opCode = 0x0E;
	uint8_t testVal = 0x27;
	uint16_t pcVal = 0x4000;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) + (addrLB);

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}

TEST_F(Core6502Tests_ASL, ASL_ABSOLUTE_X_NEG) {

	// Create test values
 	uint8_t opCode = 0x1E;
	uint8_t testVal = 0x40;
	uint16_t pcVal = 0x4000;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint8_t xVal = 0x10;
	uint16_t addr = (addrUB << 8) + (addrLB);

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr + xVal] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}
TEST_F(Core6502Tests_ASL, ASL_ABSOLUTE_X_END_ZERO) {

	// Create test values
 	uint8_t opCode = 0x1E;
	uint8_t testVal = 0x80;
	uint16_t pcVal = 0x4000;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint8_t xVal = 0x10;
	uint16_t addr = (addrUB << 8) + (addrLB);

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr + xVal] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}
TEST_F(Core6502Tests_ASL, ASL_ABSOLUTE_X_INIT_ZERO) {

	// Create test values
 	uint8_t opCode = 0x1E;
	uint8_t testVal = 0x00;
	uint16_t pcVal = 0x4000;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint8_t xVal = 0x10;
	uint16_t addr = (addrUB << 8) + (addrLB);

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr + xVal] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, 0);

}
TEST_F(Core6502Tests_ASL, ASL_ABSOLUTE_X) {

	// Create test values
 	uint8_t opCode = 0x1E;
	uint8_t testVal = 0x27;
	uint16_t pcVal = 0x4000;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint8_t xVal = 0x10;
	uint16_t addr = (addrUB << 8) + (addrLB);

	// Set registers
	cpu->registers.PC = pcVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr + xVal] = testVal;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check tests
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));

}

