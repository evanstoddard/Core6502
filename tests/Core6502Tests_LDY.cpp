#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_LDY : public testing::Test
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

// Checks all LDY instructions

// LDY Immediate
TEST_F(Core6502Tests_LDY, Test_LDY_Immediate_Positive) {
    
    // Create test values
    uint8_t opCode = 0xA0;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_LDY, Test_LDY_Immediate_Negative) {
    
    // Create test values
    uint8_t opCode = 0xA0;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0x80;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

}
TEST_F(Core6502Tests_LDY, Test_LDY_Immediate_Zero) {
    
    // Create test values
    uint8_t opCode = 0xA0;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0x0;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}

// LDY Zero Page
TEST_F(Core6502Tests_LDY, Test_LDY_Zero_Page_Positive) {
    
    // Create test values
    uint8_t opCode = 0xA4;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_LDY, Test_LDY_Zero_Page_Negative) {
    
    // Create test values
    uint8_t opCode = 0xA4;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0x80;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

}
TEST_F(Core6502Tests_LDY, Test_LDY_Zero_Page_Zero) {
    
    // Create test values
    uint8_t opCode = 0xA4;
    uint16_t pcVal = 0x4000;
    uint8_t addr = 0xFF;
    uint8_t aTestVal = 0x0;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = addr;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}

// LDY Zero Page X
TEST_F(Core6502Tests_LDY, Test_LDY_Zero_Page_X_Positive) {
    
    // Create test values
    uint8_t opCode = 0xB4;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t xVal = 0x10;
    uint8_t addr = zeroPageAddr + xVal;
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_LDY, Test_LDY_Zero_Page_X_Negative) {
    
    // Create test values
    uint8_t opCode = 0xB4;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t xVal = 0x10;
    uint8_t addr = zeroPageAddr + xVal;
    uint8_t aTestVal = 0x80;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

}
TEST_F(Core6502Tests_LDY, Test_LDY_Zero_Page_X_Zero) {
    
    // Create test values
    uint8_t opCode = 0xB4;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t xVal = 0x10;
    uint8_t addr = zeroPageAddr + xVal;
    uint8_t aTestVal = 0x0;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}

// LDY Absolute
TEST_F(Core6502Tests_LDY, Test_LDY_Absolute_Positive) {
    
    // Create test values
    uint8_t opCode = 0xAC;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_LDY, Test_LDY_Absolute_Negative) {
    
    // Create test values
   uint8_t opCode = 0xAC;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0x80;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

}
TEST_F(Core6502Tests_LDY, Test_LDY_Absolute_Zero) {
    
    // Create test values
   uint8_t opCode = 0xAC;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0x0;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}

// LDY Absolute X
TEST_F(Core6502Tests_LDY, Test_LDY_Absolute_X_Positive) {
    
    // Create test values
    uint8_t opCode = 0xBC;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t xVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + xVal;
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_LDY, Test_LDY_Absolute_X_Negative) {
    
    // Create test values
    uint8_t opCode = 0xBC;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t xVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + xVal;
    uint8_t aTestVal = 0x80;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.ZeroFlag, 0);

}
TEST_F(Core6502Tests_LDY, Test_LDY_Absolute_X_Zero) {
    
    // Create test values
    uint8_t opCode = 0xBC;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t xVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + xVal;
    uint8_t aTestVal = 0x0;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.Y,aTestVal);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.ZeroFlag, 1);

}
