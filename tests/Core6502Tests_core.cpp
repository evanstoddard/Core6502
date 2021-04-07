#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_Core : public testing::Test
{
public:
    uint8_t mem[0xFFFF];
	Core6502::CPU *cpu;
    
	virtual void SetUp()
	{   
        mem[0xFFFC] = 0xEF;
        mem[0xFFFD] = 0xBE;
        cpu = new Core6502::CPU(mem);
	}

	virtual void TearDown()
	{
        delete cpu;
	}
};

TEST_F(Core6502Tests_Core, Test_CPU_Reset) {
    
    cpu->reset();
    EXPECT_EQ(cpu->registers.PC,0xBEEF);
}