#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_Core : public testing::Test
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

// Validates that CPU sets PC to value at reset vector
// And that Registers are set to 0 and flags are set
// To default values
TEST_F(Core6502Tests_Core, Test_CPU_Reset) {
    
    // Set reset vector to 0xCAFE
    mem[0xFFFC] = 0xFE;
    mem[0xFFFD] = 0xCA;

    // Reset CPU
    cpu->reset();

    // Check Program Counter has been set 
    EXPECT_EQ(cpu->registers.PC,0xCAFE);

    // Validate registers are set to default values
    EXPECT_EQ(cpu->registers.SP, 0x0);
    EXPECT_EQ(cpu->registers.A, 0x0);
    EXPECT_EQ(cpu->registers.X, 0x0);
    EXPECT_EQ(cpu->registers.Y, 0x0);
    
    // Validate flags are set to appropriate defaults
    // Zero should be 1
    // Interrupts should be disabled
    // All others 0
    EXPECT_EQ(cpu->status.ZeroFlag, 1);
    EXPECT_EQ(cpu->status.InterruptDisable, 1);
    EXPECT_EQ(cpu->status.BreakCommand, 0);
    EXPECT_EQ(cpu->status.CarryFlag, 0);
    EXPECT_EQ(cpu->status.DecimalMode, 0);
    EXPECT_EQ(cpu->status.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.OverflowFlag, 0);
    EXPECT_EQ(cpu->status.UserFlag, 0);
    
}