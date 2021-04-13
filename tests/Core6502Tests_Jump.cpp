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

// Can copy this file to make other tests
TEST_F(Core6502Tests_Jump, Test_JMP_Absolute) {
    
	// Test values
	uint16_t pcVal = 0x4000;
	uint16_t addrLB = 0xFE;
	uint16_t addrUB = 0xCA;
	

}