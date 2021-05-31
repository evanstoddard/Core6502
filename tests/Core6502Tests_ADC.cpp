#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_ADC : public testing::Test
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

TEST_F(Core6502Tests_ADC, ADC_IMMEDIATE_POSITIVE) {
    
	// Test values
	uint8_t opCode = 0x69;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x10;
	uint8_t testVal = 0x20;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);

}
TEST_F(Core6502Tests_ADC, ADC_IMMEDIATE_NEGATIVE) {
    
	// Test values
	uint8_t opCode = 0x69;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x85;
	uint8_t testVal = 0x81;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_IMMEDIATE_POSITIVE_WITH_CARRY) {
    
	// Test values
	uint8_t opCode = 0x69;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x2;
	uint8_t testVal = 0x3;
	uint8_t carryVal = 0x1;
	uint16_t addedVal = aVal + testVal + carryVal;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_IMMEDIATE_NEGATIVE_WITH_CARRY) {
    
	// Test values
	uint8_t opCode = 0x69;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x82;
	uint8_t testVal = 0x83;
	uint8_t carryVal = 0x1;
	uint16_t addedVal = aVal + testVal + carryVal;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_IMMEDIATE_POSITIVE_NEGATIVE) {
    
	// Test values
	uint8_t opCode = 0x69;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x40;
	uint8_t testVal = 0x80;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_IMMEDIATE_NEGATIVE_POSITIVE) {
    
	// Test values
	uint8_t opCode = 0x69;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x80;
	uint8_t testVal = 0x40;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_IMMEDIATE_POSITIVE_OVERFLOW) {
    
	// Test values
	uint8_t opCode = 0x69;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x7F;
	uint8_t testVal = 0x1;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_IMMEDIATE_NEGATIVE_OVERFLOW) {
    
	// Test values
	uint8_t opCode = 0x69;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0xFF;
	uint8_t testVal = 0x80;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_IMMEDIATE_CARRY) {
    
	// Test values
	uint8_t opCode = 0x69;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0xFF;
	uint8_t testVal = 0x1;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}

TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_POSITIVE) {
    
	// Test values
	uint8_t opCode = 0x65;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x10;
	uint8_t testVal = 0x20;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);

}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_NEGATIVE) {
    
	// Test values
	uint8_t opCode = 0x65;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x85;
	uint8_t testVal = 0x81;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_POSITIVE_WITH_CARRY) {
    
	// Test values
	uint8_t opCode = 0x65;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x2;
	uint8_t testVal = 0x3;
	uint8_t carryVal = 0x1;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_NEGATIVE_WITH_CARRY) {
    
	// Test values
	uint8_t opCode = 0x65;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x82;
	uint8_t testVal = 0x83;
	uint8_t carryVal = 0x1;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_POSITIVE_NEGATIVE) {
    
	// Test values
	uint8_t opCode = 0x65;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x40;
	uint8_t testVal = 0x80;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_NEGATIVE_POSITIVE) {
    
	// Test values
	uint8_t opCode = 0x65;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x80;
	uint8_t testVal = 0x40;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_POSITIVE_OVERFLOW) {
    
	// Test values
	uint8_t opCode = 0x65;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x7F;
	uint8_t testVal = 0x1;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_NEGATIVE_OVERFLOW) {
    
	// Test values
	uint8_t opCode = 0x65;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0xFF;
	uint8_t testVal = 0x80;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_CARRY) {
    
	// Test values
	uint8_t opCode = 0x65;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0xFF;
	uint8_t testVal = 0x1;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}

TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_X_POSITIVE) {
    
	// Test values
	uint8_t opCode = 0x75;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x10;
	uint8_t testVal = 0x20;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);

}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_X_NEGATIVE) {
    
	// Test values
	uint8_t opCode = 0x75;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x85;
	uint8_t testVal = 0x81;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_X_POSITIVE_WITH_CARRY) {
    
	// Test values
	uint8_t opCode = 0x75;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x2;
	uint8_t testVal = 0x3;
	uint8_t carryVal = 0x1;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_X_NEGATIVE_WITH_CARRY) {
    
	// Test values
	uint8_t opCode = 0x75;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x82;
	uint8_t testVal = 0x83;
	uint8_t carryVal = 0x1;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_X_POSITIVE_NEGATIVE) {
    
	// Test values
	uint8_t opCode = 0x75;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x40;
	uint8_t testVal = 0x80;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_X_NEGATIVE_POSITIVE) {
    
	// Test values
	uint8_t opCode = 0x75;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x80;
	uint8_t testVal = 0x40;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_X_POSITIVE_OVERFLOW) {
    
	// Test values
	uint8_t opCode = 0x75;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x7F;
	uint8_t testVal = 0x1;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_X_NEGATIVE_OVERFLOW) {
    
	// Test values
	uint8_t opCode = 0x75;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0xFF;
	uint8_t testVal = 0x80;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ZERO_PAGE_X_CARRY) {
    
	// Test values
	uint8_t opCode = 0x75;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0xFF;
	uint8_t testVal = 0x1;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint16_t addr = 0x40;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}

TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_POSITIVE) {
    
	// Test values
	uint8_t opCode = 0x6D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x10;
	uint8_t testVal = 0x20;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);

}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_NEGATIVE) {
    
	// Test values
	uint8_t opCode = 0x6D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x85;
	uint8_t testVal = 0x81;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_POSITIVE_WITH_CARRY) {
    
	// Test values
	uint8_t opCode = 0x6D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x2;
	uint8_t testVal = 0x3;
	uint8_t carryVal = 0x1;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_NEGATIVE_WITH_CARRY) {
    
	// Test values
	uint8_t opCode = 0x6D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x82;
	uint8_t testVal = 0x83;
	uint8_t carryVal = 0x1;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x00;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_POSITIVE_NEGATIVE) {
    
	// Test values
	uint8_t opCode = 0x6D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x40;
	uint8_t testVal = 0x80;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_NEGATIVE_POSITIVE) {
    
	// Test values
	uint8_t opCode = 0x6D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x80;
	uint8_t testVal = 0x40;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_POSITIVE_OVERFLOW) {
    
	// Test values
	uint8_t opCode = 0x6D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x7F;
	uint8_t testVal = 0x1;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_NEGATIVE_OVERFLOW) {
    
	// Test values
	uint8_t opCode = 0x6D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0xFF;
	uint8_t testVal = 0x80;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_CARRY) {
    
	// Test values
	uint8_t opCode = 0x6D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0xFF;
	uint8_t testVal = 0x1;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}

TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_X_POSITIVE) {
    
	// Test values
	uint8_t opCode = 0x7D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x10;
	uint8_t testVal = 0x20;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);

}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_X_NEGATIVE) {
    
	// Test values
	uint8_t opCode = 0x7D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x85;
	uint8_t testVal = 0x81;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_X_POSITIVE_WITH_CARRY) {
    
	// Test values
	uint8_t opCode = 0x7D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x2;
	uint8_t testVal = 0x3;
	uint8_t carryVal = 0x1;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_X_NEGATIVE_WITH_CARRY) {
    
	// Test values
	uint8_t opCode = 0x7D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x82;
	uint8_t testVal = 0x83;
	uint8_t carryVal = 0x1;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_X_POSITIVE_NEGATIVE) {
    
	// Test values
	uint8_t opCode = 0x7D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x40;
	uint8_t testVal = 0x80;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_X_NEGATIVE_POSITIVE) {
    
	// Test values
	uint8_t opCode = 0x7D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x80;
	uint8_t testVal = 0x40;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_X_POSITIVE_OVERFLOW) {
    
	// Test values
	uint8_t opCode = 0x7D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x7F;
	uint8_t testVal = 0x1;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_X_NEGATIVE_OVERFLOW) {
    
	// Test values
	uint8_t opCode = 0x7D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0xFF;
	uint8_t testVal = 0x80;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_X_CARRY) {
    
	// Test values
	uint8_t opCode = 0x7D;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0xFF;
	uint8_t testVal = 0x1;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x10;
	uint8_t yVal = 0x0;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + xVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}

TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_Y_POSITIVE) {
    
	// Test values
	uint8_t opCode = 0x79;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x10;
	uint8_t testVal = 0x20;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x10;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + yVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);

}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_Y_NEGATIVE) {
    
	// Test values
	uint8_t opCode = 0x79;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x85;
	uint8_t testVal = 0x81;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x10;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + yVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_Y_POSITIVE_WITH_CARRY) {
    
	// Test values
	uint8_t opCode = 0x79;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x2;
	uint8_t testVal = 0x3;
	uint8_t carryVal = 0x1;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x10;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + yVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_Y_NEGATIVE_WITH_CARRY) {
    
	// Test values
	uint8_t opCode = 0x79;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x82;
	uint8_t testVal = 0x83;
	uint8_t carryVal = 0x1;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x10;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + yVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_Y_POSITIVE_NEGATIVE) {
    
	// Test values
	uint8_t opCode = 0x79;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x40;
	uint8_t testVal = 0x80;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x10;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + yVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_Y_NEGATIVE_POSITIVE) {
    
	// Test values
	uint8_t opCode = 0x79;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x80;
	uint8_t testVal = 0x40;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x10;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + yVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_Y_POSITIVE_OVERFLOW) {
    
	// Test values
	uint8_t opCode = 0x79;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0x7F;
	uint8_t testVal = 0x1;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x10;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + yVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_Y_NEGATIVE_OVERFLOW) {
    
	// Test values
	uint8_t opCode = 0x79;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0xFF;
	uint8_t testVal = 0x80;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x10;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + yVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}
TEST_F(Core6502Tests_ADC, ADC_ABSOLUTE_Y_CARRY) {
    
	// Test values
	uint8_t opCode = 0x79;
	uint16_t pcVal = 0x4000;
	uint8_t aVal = 0xFF;
	uint8_t testVal = 0x1;
	uint8_t carryVal = 0x0;
	uint16_t addedVal = aVal + testVal + carryVal;
	uint8_t xVal = 0x0;
	uint8_t yVal = 0x10;
	uint8_t addrUB = 0xCA;
	uint8_t addrLB = 0xFE;
	uint16_t addr = (addrUB << 8) | addrLB;

	// Set operations
	cpu->registers.PC = pcVal;
	cpu->registers.A = aVal;
	cpu->registers.X = xVal;
	cpu->registers.Y = yVal;
	cpu->mem[pcVal] = addr;
	cpu->mem[addr + yVal] = testVal;

	// Perform operation
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Overflow Check
	bool overflow = false;
	overflow =  (bool)((aVal & 0x80) & (testVal & 0x80) & ~(addedVal & 0x80));
    overflow |= (bool)(~(aVal & 0x80) & ~(testVal & 0x80) & (addedVal & 0x80));

	// Check values
	EXPECT_EQ(cpu->registers.A, (uint8_t)(aVal + testVal));
	EXPECT_EQ(cpu->status.bitfield.CarryFlag, (bool)((uint16_t)(addedVal) > 255));
	EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (bool)((uint8_t)(addedVal) == 0x0));
	EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)((uint8_t)(addedVal) & 0x80));
	EXPECT_EQ(cpu->status.bitfield.OverflowFlag, overflow);
}