#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_ROL : public testing::Test
{
public:
    uint8_t mem[0xFFFF];
	Core6502::CPU *cpu;
    
	virtual void SetUp()
	{  
        // Create CPU
        cpu = new Core6502::CPU(mem);
		cpu->reset();
	}

	virtual void TearDown()
	{
        delete cpu;
	}
};

TEST_F(Core6502Tests_ROL, ROL_ACCUMULATOR_ROL) {

	// Create test values
	uint8_t opCode = 0x2A;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x1;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->registers.A = testVal;
	cpu->status.bitfield.CarryFlag = carryFlag;
	

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->registers.A, (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->registers.A);
    
}
TEST_F(Core6502Tests_ROL, ROL_ACCUMULATOR_FROM_CARRY) {

	// Create test values
	uint8_t opCode = 0x2A;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x0;
	uint8_t carryFlag = 1;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->registers.A = testVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->registers.A, (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->registers.A);
    
}
TEST_F(Core6502Tests_ROL, ROL_ACCUMULATOR_TO_CARRY) {

	// Create test values
	uint8_t opCode = 0x2A;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0xC0;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->registers.A = testVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->registers.A, (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->registers.A);
    
}
TEST_F(Core6502Tests_ROL, ROL_ACCUMULATOR_TO_CARRY_ZERO) {

	// Create test values
	uint8_t opCode = 0x2A;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x80;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->registers.A = testVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check
	EXPECT_EQ(cpu->registers.A, (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->registers.A);
    
}
TEST_F(Core6502Tests_ROL, ROL_ACCUMULATOR_ZERO) {

	// Create test values
	uint8_t opCode = 0x2A;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x0;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->registers.A = testVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check
	EXPECT_EQ(cpu->registers.A, (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->registers.A);
    
}

TEST_F(Core6502Tests_ROL, ROL_ZERO_PAGE_ROL) {

	// Create test values
	uint8_t opCode = 0x26;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x1;
	uint8_t addr	= 0x40;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr] = testVal;
	cpu->status.bitfield.CarryFlag = carryFlag;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ZERO_PAGE_FROM_CARRY) {

	// Create test values
	uint8_t opCode = 0x26;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x0;
	uint8_t addr	= 0x40;
	uint8_t carryFlag = 1;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr] = testVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ZERO_PAGE_TO_CARRY) {

	// Create test values
	uint8_t opCode = 0x26;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0xC0;
	uint8_t addr	= 0x40;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr] = testVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ZERO_PAGE_TO_CARRY_ZERO) {

	// Create test values
	uint8_t opCode = 0x26;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x80;
	uint8_t addr	= 0x40;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr] = testVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ZERO_PAGE_ZERO) {

	// Create test values
	uint8_t opCode = 0x26;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x0;
	uint8_t addr	= 0x40;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr] = testVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check
	EXPECT_EQ(cpu->mem[addr], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr]);
    
}

TEST_F(Core6502Tests_ROL, ROL_ZERO_PAGE_X_ROL) {

	// Create test values
	uint8_t opCode = 0x36;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x1;
	uint8_t addr	= 0x40;
	uint8_t xVal	= 0x10;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ZERO_PAGE_X_FROM_CARRY) {

	// Create test values
	uint8_t opCode = 0x36;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x0;
	uint8_t addr	= 0x40;
	uint8_t xVal	= 0x10;
	uint8_t carryFlag = 1;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ZERO_PAGE_X_TO_CARRY) {

	// Create test values
	uint8_t opCode = 0x36;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0xC0;
	uint8_t addr	= 0x40;
	uint8_t xVal	= 0x10;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ZERO_PAGE_X_TO_CARRY_ZERO) {

	// Create test values
	uint8_t opCode = 0x36;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x80;
	uint8_t addr	= 0x40;
	uint8_t xVal	= 0x10;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ZERO_PAGE_X_ZERO) {

	// Create test values
	uint8_t opCode = 0x36;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x0;
	uint8_t addr	= 0x40;
	uint8_t xVal	= 0x10;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}

TEST_F(Core6502Tests_ROL, ROL_ABSOLUTE_ROL) {

	// Create test values
	uint8_t opCode = 0x2E;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x1;
	uint8_t addrUB	= 0xCA;
	uint8_t addrLB  = 0xFE;
	uint16_t addr	= (addrUB << 8) | addrLB;
	uint8_t xVal	= 0x0;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ABSOLUTE_FROM_CARRY) {

	// Create test values
	uint8_t opCode = 0x2E;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x0;
	uint8_t addrUB	= 0xCA;
	uint8_t addrLB  = 0xFE;
	uint16_t addr	= (addrUB << 8) | addrLB;
	uint8_t xVal	= 0x0;
	uint8_t carryFlag = 1;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ABSOLUTE_TO_CARRY) {

	// Create test values
	uint8_t opCode = 0x2E;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0xC0;
	uint8_t addrUB	= 0xCA;
	uint8_t addrLB  = 0xFE;
	uint16_t addr	= (addrUB << 8) | addrLB;
	uint8_t xVal	= 0x0;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ABSOLUTE_TO_CARRY_ZERO) {

	// Create test values
	uint8_t opCode = 0x2E;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x80;
	uint8_t addrUB	= 0xCA;
	uint8_t addrLB  = 0xFE;
	uint16_t addr	= (addrUB << 8) | addrLB;
	uint8_t xVal	= 0x0;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ABSOLUTE_ZERO) {

	// Create test values
	uint8_t opCode = 0x2E;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x0;
	uint8_t addrUB	= 0xCA;
	uint8_t addrLB  = 0xFE;
	uint16_t addr	= (addrUB << 8) | addrLB;
	uint8_t xVal	= 0x00;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}

TEST_F(Core6502Tests_ROL, ROL_ABSOLUTE_X_ROL) {

	// Create test values
	uint8_t opCode = 0x3E;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x1;
	uint8_t addrUB	= 0xCA;
	uint8_t addrLB  = 0xFE;
	uint16_t addr	= (addrUB << 8) | addrLB;
	uint8_t xVal	= 0x10;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;
	
	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ABSOLUTE_X_FROM_CARRY) {

	// Create test values
	uint8_t opCode = 0x3E;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x0;
	uint8_t addrUB	= 0xCA;
	uint8_t addrLB  = 0xFE;
	uint16_t addr	= (addrUB << 8) | addrLB;
	uint8_t xVal	= 0x10;
	uint8_t carryFlag = 1;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ABSOLUTE_X_TO_CARRY) {

	// Create test values
	uint8_t opCode = 0x3E;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0xC0;
	uint8_t addrUB	= 0xCA;
	uint8_t addrLB  = 0xFE;
	uint16_t addr	= (addrUB << 8) | addrLB;
	uint8_t xVal	= 0x10;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);
	
	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ABSOLUTE_X_TO_CARRY_ZERO) {

	// Create test values
	uint8_t opCode = 0x3E;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x80;
	uint8_t addrUB	= 0xCA;
	uint8_t addrLB  = 0xFE;
	uint16_t addr	= (addrUB << 8) | addrLB;
	uint8_t xVal	= 0x10;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
TEST_F(Core6502Tests_ROL, ROL_ABSOLUTE_X_ZERO) {

	// Create test values
	uint8_t opCode = 0x3E;
	uint16_t pcVal = 0x4000;
	uint8_t testVal = 0x0;
	uint8_t addrUB	= 0xCA;
	uint8_t addrLB  = 0xFE;
	uint16_t addr	= (addrUB << 8) | addrLB;
	uint8_t xVal	= 0x10;
	uint8_t carryFlag = 0;

	// Set registers an memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;
	cpu->registers.X = xVal;
	cpu->status.bitfield.CarryFlag = carryFlag;

	// Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check
	EXPECT_EQ(cpu->mem[addr + xVal], (uint8_t)(testVal << 1) | carryFlag);
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)(testVal & 0x80));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->mem[addr + xVal] & 0x80));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, !cpu->mem[addr + xVal]);
    
}
