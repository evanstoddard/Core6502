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
    EXPECT_EQ(cpu->registers.SP, 0xFF);
    EXPECT_EQ(cpu->registers.A, 0x0);
    EXPECT_EQ(cpu->registers.X, 0x0);
    EXPECT_EQ(cpu->registers.Y, 0x0);
    
    // Validate flags are set to appropriate defaults
    // Zero should be 1
    // Interrupts should be disabled
    // All others 0
    EXPECT_EQ(cpu->status.bitfield.ZeroFlag, 1);
    EXPECT_EQ(cpu->status.bitfield.InterruptDisable, 1);
    EXPECT_EQ(cpu->status.bitfield.BreakCommand, 0);
    EXPECT_EQ(cpu->status.bitfield.CarryFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.DecimalMode, 0);
    EXPECT_EQ(cpu->status.bitfield.NegativeFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.OverflowFlag, 0);
    EXPECT_EQ(cpu->status.bitfield.UserFlag, 0);
    
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
    uint8_t memValLB = 0xEF;
    uint8_t memValUB = 0xBE;
    uint16_t memVal = memValLB + (memValUB << 8);

    // Set program counter and mem to known value
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = memValLB;
    cpu->mem[pcVal+1] = memValUB;

    // Fetch address
    uint16_t addr = cpu->absoluteAddr(*cpu);

    // Validate fetched address is what we expect
    EXPECT_EQ(addr, memVal);

}
TEST_F(Core6502Tests_Core, Test_Absolute_X_Addressing) {

    // Initial values
    uint16_t pcVal = 0x4000;
    uint8_t memValLB = 0xEF;
    uint8_t memValUB = 0xBE;
    uint16_t memVal = memValLB + (memValUB << 8);
    uint8_t xVal = 0x6;

    // Set program counter and mem to known value
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = memValLB;
    cpu->mem[pcVal+1] = memValUB;

    // Fetch address
    uint16_t addr = cpu->absoluteXAddr(*cpu);

    // Validate fetched address is what we expect
    EXPECT_EQ(addr, memVal + xVal);

}
TEST_F(Core6502Tests_Core, Test_Absolute_Y_Addressing) {

   // Initial values
    uint16_t pcVal = 0x4000;
    uint8_t memValLB = 0xEF;
    uint8_t memValUB = 0xBE;
    uint16_t memVal = memValLB + (memValUB << 8);
    uint8_t yVal = 0x6;

    // Set program counter and mem to known value
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = memValLB;
    cpu->mem[pcVal+1] = memValUB;

    // Fetch address
    uint16_t addr = cpu->absoluteYAddr(*cpu);

    // Validate fetched address is what we expect
    EXPECT_EQ(addr, memVal + yVal);

}
TEST_F(Core6502Tests_Core, Test_Zero_Page) {

   // Initial values
    uint16_t pcVal = 0x4000;
    uint8_t memVal = 0x40;

    // Set program counter and mem to known value
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = memVal;
   
    // Fetch address
    uint8_t addr = cpu->zeroPageAddr(*cpu);

    // Validate fetched address is what we expect
    EXPECT_EQ(addr, memVal);

}
TEST_F(Core6502Tests_Core, Test_Zero_Page_X) {

   // Initial values
    uint16_t pcVal = 0x4000;
    uint8_t memVal = 0x40;
    uint8_t xVal = 0x20;

    // Set program counter and mem to known value
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = memVal;
   
    // Fetch address
    uint8_t addr = cpu->zeroPageXAddr(*cpu);

    // Validate fetched address is what we expect
    EXPECT_EQ(addr, memVal + xVal);

}
TEST_F(Core6502Tests_Core, Test_Zero_Page_X_Wrap_Around) {

   // Initial values
    uint16_t pcVal = 0x4000;
    uint8_t memVal = 0xFF;
    uint8_t xVal = 0x20;

    // Set program counter and mem to known value
    cpu->registers.PC = pcVal;
    cpu->registers.X = xVal;
    cpu->mem[pcVal] = memVal;
   
    // Fetch address
    uint16_t addr = cpu->zeroPageXAddr(*cpu);

    // Validate fetched address is what we expect
    EXPECT_LT(addr, 0x100);
    EXPECT_EQ(addr, (uint8_t)(memVal + xVal));

}
TEST_F(Core6502Tests_Core, Test_Zero_Page_Y) {

   // Initial values
    uint16_t pcVal = 0x4000;
    uint8_t memVal = 0x40;
    uint8_t yVal = 0x20;

    // Set program counter and mem to known value
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = memVal;
   
    // Fetch address
    uint8_t addr = cpu->zeroPageYAddr(*cpu);

    // Validate fetched address is what we expect
    EXPECT_EQ(addr, memVal + yVal);

}
TEST_F(Core6502Tests_Core, Test_Zero_Page_Y_Wrap_Around) {

   // Initial values
    uint16_t pcVal = 0x4000;
    uint8_t memVal = 0xFF;
    uint8_t yVal = 0x20;

    // Set program counter and mem to known value
    cpu->registers.PC = pcVal;
    cpu->registers.Y = yVal;
    cpu->mem[pcVal] = memVal;
   
    // Fetch address
    uint16_t addr = cpu->zeroPageYAddr(*cpu);

    // Validate fetched address is what we expect
    EXPECT_LT(addr, 0x100);
    EXPECT_EQ(addr, (uint8_t)(memVal + yVal));

}
TEST_F(Core6502Tests_Core, Test_Indirect) {

    // Initial values
    uint16_t pcVal = 0x4000;
    uint8_t indirectLB = 0xFE;
    uint8_t indirectUB = 0xCA;
    uint8_t memLB = 0xBE;
    uint8_t memUB = 0xBA;
    uint16_t indirectAddr = indirectLB + (indirectUB << 8);
    uint16_t memAddr = memLB + (memUB << 8);

    // Set PC and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = indirectLB;
    cpu->mem[pcVal + 1] = indirectUB;
    cpu->mem[indirectAddr] = memLB;
    cpu->mem[indirectAddr + 1] = memUB;

    // Validate fetched address is expected
    uint16_t addr = cpu->indirectAddr(*cpu);

    EXPECT_EQ(addr, memAddr);
}
TEST_F(Core6502Tests_Core, Test_Indirect_Page_Boundary_Bug) {

    // Initial values
    uint16_t pcVal = 0x4000;
    uint8_t indirectLB = 0xFF;
    uint8_t indirectUB = 0xCA;
    uint8_t memLB = 0xBE;
    uint8_t memUB = 0xBA;
    uint16_t indirectAddr = indirectLB + (indirectUB << 8);
    uint16_t memAddr = memLB + (memUB << 8);

    // Set PC and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = indirectLB;
    cpu->mem[pcVal + 1] = indirectUB;
    cpu->mem[indirectAddr] = memLB;
    cpu->mem[indirectAddr & 0xFF00] = memUB;

    // Validate fetched address is expected
    uint16_t addr = cpu->indirectAddr(*cpu);

    EXPECT_EQ(addr, memAddr);
}
TEST_F(Core6502Tests_Core, Test_Relative_Positive_Positive) {

    // Initial values
    uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;

    // Set PC and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = offset;
    
    // Validate fetched address is expected
    uint16_t addr = cpu->relativeAddr(*cpu);

    EXPECT_EQ(addr, 0x4040 + 1);
}
TEST_F(Core6502Tests_Core, Test_Relative_Positive_Negative) {

    // Initial values
    uint16_t pcVal = 0x4000;
    int8_t offset = -0x40;

    // Set PC and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = offset;
    
    // Validate fetched address is expected
    uint16_t addr = cpu->relativeAddr(*cpu);

    EXPECT_EQ(addr, 0x3FC0 + 1);
}
TEST_F(Core6502Tests_Core, Test_Relative_Negative_Positive) {

    // Initial values
    uint16_t pcVal = 0x8000;
    int8_t offset = 0x40;

    // Set PC and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = offset;
    
    // Validate fetched address is expected
    uint16_t addr = cpu->relativeAddr(*cpu);

    EXPECT_EQ(addr, 0x8040 + 1);
}
TEST_F(Core6502Tests_Core, Test_Relative_Negative_Negative) {

    // Initial values
    uint16_t pcVal = 0x8000;
    int8_t offset = -0x40;

    // Set PC and memory
    cpu->registers.PC = pcVal;
    cpu->mem[pcVal] = offset;
    
    // Validate fetched address is expected
    uint16_t addr = cpu->relativeAddr(*cpu);

    EXPECT_EQ(addr, 0x7FC0 + 1);
}
