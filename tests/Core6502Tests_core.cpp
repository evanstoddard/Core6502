#include <gtest/gtest.h>
#include "Core6502.hpp"

class Core6502Tests_Core : public testing::Test
{
public:

	Core6502::CPU cpu();

	virtual void SetUp()
	{
		
	}

	virtual void TearDown()
	{
	}
};

TEST_F(Core6502Tests_Core, Test_CPU_Reset) {
    

    EXPECT_EQ(1,1);
}