#include <gtest/gtest.h>
#include<iostream>
class MyClass
{   
    int baseVal;
public:
    MyClass(int _bv) : baseVal(_bv) {}
    void increment (int byValue)
    {
        baseVal+=byValue;
    }
    int getValue() {return baseVal;}
};
struct TestMyClass : testing::Test
{
    MyClass *mc;
    void SetUp(){mc =new MyClass(100);}
    void TearDown(){delete mc;}
};
TEST_F(TestMyClass, Increment_by_5)
{
    //act
    mc->increment(5);
    //assert
    ASSERT_EQ(mc->getValue(),105);
}
TEST(test_suite1,test1)
{
    //Arange
    int value=100;
    int increment=5;
    //act
    value=value+increment;
    //assert
    ASSERT_EQ(value,105);
}
int main(int argc, char**argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
