#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_AND : public testing::Test
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

// AND Immediate
TEST_F(Core6502Tests_AND, Test_AND_Immediate_Positive) {
    
    // Create test values
    uint8_t opCode = 0x29;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = mask;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

    
}
TEST_F(Core6502Tests_AND, Test_AND_Immediate_Negative) {
    
    // Create test values
    uint8_t opCode = 0x29;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x8F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = mask;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

    
}
TEST_F(Core6502Tests_AND, Test_AND_Immediate_Zero) {
    
    // Create test values
    uint8_t opCode = 0x29;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = mask;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

    
}

// AND Zero Page
TEST_F(Core6502Tests_AND, Test_AND_Zero_Page_Positive) {
    
    // Create test values
    uint8_t opCode = 0x25;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

    
}
TEST_F(Core6502Tests_AND, Test_AND_Zero_Page_Negative) {
    
    // Create test values
    uint8_t opCode = 0x25;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x8F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

}
TEST_F(Core6502Tests_AND, Test_AND_Zero_Page_Zero) {
    
    // Create test values
    uint8_t opCode = 0x25;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

}

// AND Zero Page X
TEST_F(Core6502Tests_AND, Test_AND_Zero_Page_X_Positive) {
    
    // Create test values
    uint8_t opCode = 0x35;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t xVal = 0x10;
    uint8_t addr = zeroPageAddr + xVal;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

    
}
TEST_F(Core6502Tests_AND, Test_AND_Zero_Page_X_Negative) {
    
    // Create test values
    uint8_t opCode = 0x35;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t xVal = 0x10;
    uint8_t addr = zeroPageAddr + xVal;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x8F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

}
TEST_F(Core6502Tests_AND, Test_AND_Zero_Page_X_Zero) {
    
    // Create test values
    uint8_t opCode = 0x35;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t xVal = 0x10;
    uint8_t addr = zeroPageAddr + xVal;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

}

// AND Absolute
TEST_F(Core6502Tests_AND, Test_AND_Absolute_Positive) {
    
    // Create test values
    uint8_t opCode = 0x2D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

}
TEST_F(Core6502Tests_AND, Test_AND_Absolute_Negative) {
    
    // Create test values
   uint8_t opCode = 0x2D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x8F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

}
TEST_F(Core6502Tests_AND, Test_AND_Absolute_Zero) {
    
    // Create test values
   uint8_t opCode = 0x2D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

}

// AND Absolute X
TEST_F(Core6502Tests_AND, Test_AND_Absolute_X_Positive) {
    
    // Create test values
    uint8_t opCode = 0x3D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t xVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + xVal;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

    
}
TEST_F(Core6502Tests_AND, Test_AND_Absolute_X_Negative) {
    
    // Create test values
    uint8_t opCode = 0x3D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t xVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + xVal;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x8F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

}
TEST_F(Core6502Tests_AND, Test_AND_Absolute_X_Zero) {
    
    // Create test values
    uint8_t opCode = 0x3D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t xVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + xVal;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

}

// AND Absolute Y
TEST_F(Core6502Tests_AND, Test_AND_Absolute_Y_Positive) {
    
    // Create test values
    uint8_t opCode = 0x39;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t yVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + yVal;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x0F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

    
}
TEST_F(Core6502Tests_AND, Test_AND_Absolute_Y_Negative) {
    
    // Create test values
    uint8_t opCode = 0x39;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t yVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + yVal;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x8F;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

}
TEST_F(Core6502Tests_AND, Test_AND_Absolute_Y_Zero) {
    
    // Create test values
    uint8_t opCode = 0x39;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t yVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + yVal;
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x00;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = mask;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal & mask);
    EXPECT_EQ(cpu->status.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.ZeroFlag, (cpu->registers.A == 0));

}
