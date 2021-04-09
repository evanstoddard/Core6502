#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_StatusFlags : public testing::Test
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

TEST_F(Core6502Tests_StatusFlags, Test_Clear_CarryFlag) {
    
    // Create test values
    uint8_t opCode = 0x18;
    cpu->status.CarryFlag = 1;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(0, cpu->status.CarryFlag);
    
}

TEST_F(Core6502Tests_StatusFlags, Test_Clear_DecimalMode) {
    
    // Create test values
    uint8_t opCode = 0xD8;
    cpu->status.DecimalMode = 1;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(0, cpu->status.DecimalMode);
    
}

TEST_F(Core6502Tests_StatusFlags, Test_Clear_InterruptDisable) {
    
    // Create test values
    uint8_t opCode = 0x58;
    cpu->status.InterruptDisable = 1;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(0, cpu->status.InterruptDisable);
    
}

TEST_F(Core6502Tests_StatusFlags, Test_Clear_OverflowFlag) {
    
    // Create test values
    uint8_t opCode = 0xB8;
    cpu->status.OverflowFlag = 1;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(0, cpu->status.OverflowFlag);
    
}

TEST_F(Core6502Tests_StatusFlags, Test_Set_CarryFlag) {
    
    // Create test values
    uint8_t opCode = 0x38;
    cpu->status.CarryFlag = 0;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(1, cpu->status.CarryFlag);
    
}

TEST_F(Core6502Tests_StatusFlags, Test_Set_DecimalMode) {
    
    // Create test values
    uint8_t opCode = 0xF8;
    cpu->status.DecimalMode = 0;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(1, cpu->status.DecimalMode);
    
}

TEST_F(Core6502Tests_StatusFlags, Test_Set_InterruptDisable) {
    
    // Create test values
    uint8_t opCode = 0x78;
    cpu->status.InterruptDisable = 0;

    // Clear Flag
    cpu->instructions[opCode].instructionFunction(*cpu, cpu->instructions[opCode]);

    // Check Status
    EXPECT_EQ(1, cpu->status.InterruptDisable);
    
}
