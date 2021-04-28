#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_LDX : public testing::Test
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

// Checks all LDX instructions

// LDX Immediate
TEST_F(Core6502Tests_LDX, Test_LDX_Immediate_Positive) {
    
    // Create test values
    uint8_t opCode = 0xA2;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_LDX, Test_LDX_Immediate_Negative) {
    
    // Create test values
    uint8_t opCode = 0xA2;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0x80;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);

}
TEST_F(Core6502Tests_LDX, Test_LDX_Immediate_Zero) {
    
    // Create test values
    uint8_t opCode = 0xA2;
    uint16_t pcVal = 0x4000;
    uint8_t aTestVal = 0x0;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);

}

// LDX Zero Page
TEST_F(Core6502Tests_LDX, Test_LDX_Zero_Page_Positive) {
    
    // Create test values
    uint8_t opCode = 0xA6;
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
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_LDX, Test_LDX_Zero_Page_Negative) {
    
    // Create test values
    uint8_t opCode = 0xA6;
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
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);

}
TEST_F(Core6502Tests_LDX, Test_LDX_Zero_Page_Zero) {
    
    // Create test values
    uint8_t opCode = 0xA6;
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
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);

}

// LDX Zero Page Y
TEST_F(Core6502Tests_LDX, Test_LDX_Zero_Page_Y_Positive) {
    
    // Create test values
    uint8_t opCode = 0xB6;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t yVal = 0x10;
    uint8_t addr = zeroPageAddr + yVal;
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_LDX, Test_LDX_Zero_Page_Y_Negative) {
    
    // Create test values
    uint8_t opCode = 0xB6;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t yVal = 0x10;
    uint8_t addr = zeroPageAddr + yVal;
    uint8_t aTestVal = 0x80;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);

}
TEST_F(Core6502Tests_LDX, Test_LDX_Zero_Page_Y_Zero) {
    
    // Create test values
    uint8_t opCode = 0xB6;
    uint16_t pcVal = 0x4000;
    uint8_t zeroPageAddr = 0x80;
    uint8_t yVal = 0x10;
    uint8_t addr = zeroPageAddr + yVal;
    uint8_t aTestVal = 0x0;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = zeroPageAddr;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);

}

// LDX Absolute
TEST_F(Core6502Tests_LDX, Test_LDX_Absolute_Positive) {
    
    // Create test values
    uint8_t opCode = 0xAE;
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
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_LDX, Test_LDX_Absolute_Negative) {
    
    // Create test values
   uint8_t opCode = 0xAE;
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
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);

}
TEST_F(Core6502Tests_LDX, Test_LDX_Absolute_Zero) {
    
    // Create test values
   uint8_t opCode = 0xAE;
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
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);

}

// LDX Absolute Y
TEST_F(Core6502Tests_LDX, Test_LDX_Absolute_Y_Positive) {
    
    // Create test values
    uint8_t opCode = 0xBE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t yVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + yVal;
    uint8_t aTestVal = 0x0A;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);

    
}
TEST_F(Core6502Tests_LDX, Test_LDX_Absolute_Y_Negative) {
    
    // Create test values
    uint8_t opCode = 0xBE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t yVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + yVal;
    uint8_t aTestVal = 0x80;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 0);

}
TEST_F(Core6502Tests_LDX, Test_LDX_Absolute_Y_Zero) {
    
    // Create test values
    uint8_t opCode = 0xBE;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xEF;
    uint8_t absoluteUB = 0xBE;
    uint8_t yVal = 0x10;
    uint16_t addr = absoluteLB + (absoluteUB << 8) + yVal;
    uint8_t aTestVal = 0x0;

    // Set Registers and memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = absoluteLB;
    cpu->mem[pcVal+1] = absoluteUB;
    cpu->mem[addr] = aTestVal;

    // Perform instruction
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.X,aTestVal);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);

}
