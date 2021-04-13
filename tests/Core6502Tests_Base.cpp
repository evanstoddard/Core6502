#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_Base : public testing::Test
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
TEST_F(Core6502Tests_Base, Test_Base_Test) {
    EXPECT_EQ(1,1);
}