#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_EOR : public testing::Test
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

// EOR Immediate
TEST_F(Core6502Tests_EOR, Test_EOR_Immediate_Positive) {
    
    // Create test values
    uint8_t opCode = 0x49;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0xF0;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = operand;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

    
}
TEST_F(Core6502Tests_EOR, Test_EOR_Immediate_Negative) {
    
    // Create test values
    uint8_t opCode = 0x49;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0x0F;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = operand;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

    
}
TEST_F(Core6502Tests_EOR, Test_EOR_Immediate_Zero) {
    
    // Create test values
    uint8_t opCode = 0x49;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0xFF;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->registers.A = aTestVal;
    cpu->mem[pcVal] = operand;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

    
}

// EOR Zero Page
TEST_F(Core6502Tests_EOR, Test_EOR_Zero_Page_Positive) {
    
    // Create test values
    uint8_t opCode = 0x45;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0xF0;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

    
}
TEST_F(Core6502Tests_EOR, Test_EOR_Zero_Page_Negative) {
    
    // Create test values
    uint8_t opCode = 0x45;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0x0F;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

}
TEST_F(Core6502Tests_EOR, Test_EOR_Zero_Page_Zero) {
    
    // Create test values
    uint8_t opCode = 0x45;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0xFF;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

}

// EOR Zero Page X
TEST_F(Core6502Tests_EOR, Test_EOR_Zero_Page_X_Positive) {
    
    // Create test values
    uint8_t opCode = 0x55;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t xVal = 0x10;
    uint8_t addr = zeroPageAddr + xVal;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0xF0;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

    
}
TEST_F(Core6502Tests_EOR, Test_EOR_Zero_Page_X_Negative) {
    
    // Create test values
    uint8_t opCode = 0x55;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t xVal = 0x10;
    uint8_t addr = zeroPageAddr + xVal;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0x0F;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

}
TEST_F(Core6502Tests_EOR, Test_EOR_Zero_Page_X_Zero) {
    
    // Create test values
    uint8_t opCode = 0x55;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t xVal = 0x10;
    uint8_t addr = zeroPageAddr + xVal;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0xFF;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

}

// EOR Absolute
TEST_F(Core6502Tests_EOR, Test_EOR_Absolute_Positive) {
    
    // Create test values
    uint8_t opCode = 0x4D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0xF0;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

}
TEST_F(Core6502Tests_EOR, Test_EOR_Absolute_Negative) {
    
    // Create test values
   uint8_t opCode = 0x4D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0x0F;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

}
TEST_F(Core6502Tests_EOR, Test_EOR_Absolute_Zero) {
    
    // Create test values
   uint8_t opCode = 0x4D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0xFF;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

}

// EOR Absolute X
TEST_F(Core6502Tests_EOR, Test_EOR_Absolute_X_Positive) {
    
    // Create test values
    uint8_t opCode = 0x5D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t xVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + xVal;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0xF0;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

    
}
TEST_F(Core6502Tests_EOR, Test_EOR_Absolute_X_Negative) {
    
    // Create test values
    uint8_t opCode = 0x5D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t xVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + xVal;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0x0F;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

}
TEST_F(Core6502Tests_EOR, Test_EOR_Absolute_X_Zero) {
    
    // Create test values
    uint8_t opCode = 0x5D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t xVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + xVal;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0xFF;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

}

// EOR Absolute Y
TEST_F(Core6502Tests_EOR, Test_EOR_Absolute_Y_Positive) {
    
    // Create test values
    uint8_t opCode = 0x59;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t yVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + yVal;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0xF0;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

    
}
TEST_F(Core6502Tests_EOR, Test_EOR_Absolute_Y_Negative) {
    
    // Create test values
    uint8_t opCode = 0x59;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t yVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + yVal;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0x0F;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

}
TEST_F(Core6502Tests_EOR, Test_EOR_Absolute_Y_Zero) {
    
    // Create test values
    uint8_t opCode = 0x59;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t yVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + yVal;
    uint8_t aTestVal = 0xFF;
    uint8_t operand = 0xFF;

    // Set Registers EOR memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = operand;
    cpu->registers.A = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check test case
    EXPECT_EQ(cpu->registers.A, aTestVal ^ operand);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, (bool)(cpu->registers.A & 0x80));
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, (cpu->registers.A == 0));

}
