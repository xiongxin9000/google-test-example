#include <gtest/gtest.h>
#include<iostream>
#include<vector>
class Stack
{
    std::vector<int> vstack={};
public:
    void push(int val){vstack.push_back(val);}
    int size(){return vstack.size();}
    int pop()
    {
        if(vstack.size()>0)
        {
            int value=vstack.back();
            vstack.pop_back();
            return value;
        }   
        else {return -1;}
    }
};
struct structTest : public testing::Test
{
    Stack s1;
    void SetUp()
    {
        int value[]={1,2,3,4,5,6,7,8,9};
        for(auto &val:value)
        {
            s1.push(val);
        }
    }
    void TearDown(){}
};
TEST_F(structTest,poptest)
{
    int lastpopedvalue=9;
    while (lastpopedvalue!=1)
    {
        ASSERT_EQ(s1.pop(),lastpopedvalue--);
    }
}
TEST_F(structTest,sizetest)
{
    int val=s1.size();
    for(val;val>0;val--)
    {
        ASSERT_NE(s1.pop(),-1);
    }
}
int main(int argc, char**argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
