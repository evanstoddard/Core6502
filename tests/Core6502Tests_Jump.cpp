#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_Jump : public testing::Test
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

// JMP Absolute
TEST_F(Core6502Tests_Jump, Test_JMP_Absolute) {
	// Test values
	uint8_t opCode = 0x4C;
	uint16_t pcVal = 0x4000;
	uint8_t addrLB = 0xFE;
	uint8_t addrUB = 0xCA;
	uint16_t addr = addrLB + (addrUB << 8);

	// Set Memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = addrLB;
	cpu->mem[pcVal + 1] = addrUB;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test case
	EXPECT_EQ(cpu->registers.PC, addr);
}

// JMP Indirect
TEST_F(Core6502Tests_Jump, Test_JMP_Indirect) {
	// Test values
	uint8_t opCode = 0x6C;
	uint16_t pcVal = 0x4000;
	uint8_t indirectLB = 0xFE;
	uint8_t indirectUB = 0xCA;
	uint8_t addrLB = 0xBE;
	uint8_t addrUB = 0xBA;
	uint16_t indirectAddr = indirectLB + (indirectUB << 8);
 	uint16_t addr = addrLB + (addrUB << 8);

	// Set Memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = indirectLB;
	cpu->mem[pcVal + 1] = indirectUB;
	cpu->mem[indirectAddr] = addrLB;
	cpu->mem[indirectAddr + 1] = addrUB;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test case
	EXPECT_EQ(cpu->registers.PC, addr);
}

// JMP Indirect Bug
TEST_F(Core6502Tests_Jump, Test_JMP_Indirect_Bug) {
	// Test values
	uint8_t opCode = 0x6C;
	uint16_t pcVal = 0x4000;
	uint8_t indirectLB = 0xFF;
	uint8_t indirectUB = 0xCA;
	uint8_t addrLB = 0xBE;
	uint8_t addrUB = 0xBA;
	uint16_t indirectAddr = indirectLB + (indirectUB << 8);
 	uint16_t addr = addrLB + (addrUB << 8);

	// Set Memory
	cpu->registers.PC = pcVal;
	cpu->mem[pcVal] = indirectLB;
	cpu->mem[pcVal + 1] = indirectUB;
	cpu->mem[indirectAddr] = addrLB;
	cpu->mem[indirectAddr & 0xFF00] = addrUB;

	// Perform Instruction
	cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

	// Check test case
	EXPECT_EQ(cpu->registers.PC, addr);
}
