#include "gtest/gtest.h"

#include "VCD_Out.hpp"

class VCD_OutTest : public ::testing::Test
{
protected:

    VCD_OutTest() {
    }

    virtual ~VCD_OutTest() {
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {

    }

    virtual void TearDown() {
//	  remove("./tst.vcd"); 
    }

    // Objects declared here can be used by all tests in the test case for Foo.
    VCD_Out vcdout;
};

TEST_F(VCD_OutTest, binary_signals) 
{
    // Exercises the Xyz feature of Foo.

    //int array[10]={1,2,4,5,6,7,8,9,10};
    vcdout.open("./tst.vcd", 1, "ms", "1.0.0");
    vcdout.define_vector(1,32, "vector");
    vcdout.define_vector(2,8, "byte");


    vcdout.set_time(0);

    vcdout.set_value(1,0x0);
    vcdout.set_value(2,0x0);

    vcdout.increment_time_ms(10);

    vcdout.set_value(1,0x1);
    vcdout.set_value(2,0xF);

    vcdout.increment_time_ms(10);

    vcdout.set_value(1,0x2);
    vcdout.set_value(2,0xa);

    vcdout.increment_time_ms(10);

    vcdout.set_value(1,0x3);
    vcdout.set_value(2,0xab);

    vcdout.increment_time_ms(10);

    vcdout.set_value(1,0x4);
    vcdout.set_value(2,0xcd);

    vcdout.increment_time_ms(10);

    vcdout.set_value(1,0x5);
    vcdout.set_value(2,0xab);

    vcdout.increment_time_ms(10);

    vcdout.set_value(1,0x6);

    vcdout.increment_time_ms(10);

    vcdout.set_value(1,0x7);

    vcdout.increment_time_ms(10);

    vcdout.set_value(1,0x12345678);

    vcdout.increment_time_ms(10);

    vcdout.set_value(1,0);

    ASSERT_TRUE( access("./tst.vcd", 0) == 0);
}
