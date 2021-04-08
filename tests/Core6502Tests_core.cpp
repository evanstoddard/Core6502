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

// Validates fetch byte returns byte at PC address and increments PC
TEST_F(Core6502Tests_Core, Test_CPU_Fetch_Byte) {

    // Set PC and a byte at given location
    uint16_t pcVal = 0x4000;
    uint8_t testVal = 0xBE;

    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = testVal;

    // Fetch value;
    uint8_t value = cpu->fetchByte();

    // Check returned value is what it was set to
    // And check that PC incremented by 1
    EXPECT_EQ(value, testVal);
    EXPECT_EQ(cpu->registers.PC, pcVal + 1);

}

// Validates Various Addressing Modes
TEST_F(Core6502Tests_Core, Test_Absolute_Addressing) {

    // Initial values
    uint16_t pcVal = 0x4000;
    uint8_t memVal = 0xBE;

    // Set program counter and mem to known value
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = memVal;

    // Fetch address
    uint8_t addr = cpu->absoluteAddr();

    // Validate fetched address is what we expect
    EXPECT_EQ(addr, memVal);

}
TEST_F(Core6502Tests_Core, Test_Absolute_X_Addressing) {

    // Initial values
    uint16_t pcVal = 0x4000;
    uint8_t xVal = 0x2;
    uint8_t memVal = 0xBE;

    // Set registers & memory
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = memVal;

    // Fetch address
    uint8_t addr = cpu->absoluteXAddr();

    // Validate fetched address is what we expect
    EXPECT_EQ(addr, memVal + xVal);

}
TEST_F(Core6502Tests_Core, Test_Absolute_Y_Addressing) {

    // Initial values
    uint16_t pcVal = 0x4000;
    uint8_t yVal = 0x2;
    uint8_t memVal = 0xBE;

    // Set registers & memory
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = memVal;

    // Fetch address
    uint8_t addr = cpu->absoluteYAddr();

    // Validate fetched address is what we expect
    EXPECT_EQ(addr, memVal + yVal);

}