#include<gtest/gtest.h>
#include<iostream>
#include<vector>
#include<gmock/gmock.h>

using namespace std;
using testing::AtLeast;
using testing::Return;
using testing::_;
class DataBaseConnect{
public:
    virtual bool login(string username,string password) {return true;}
    virtual bool login2(string username,string password) {return true;}
    virtual bool logout(string username) {return true;}
    virtual int fetchRecord() {return -1;}
};
class MockDB : public DataBaseConnect
{
public:
    MOCK_METHOD0(fetchRecord,int());
    MOCK_METHOD1(logout,bool (string username));
    MOCK_METHOD2(login, bool (string username, string password));
    MOCK_METHOD2(login2, bool (string username, string password));
};
class MyDatabase
{
    DataBaseConnect &dbc;
public:
    MyDatabase(DataBaseConnect &_dbc) : dbc(_dbc){}
    int Init(string username,string password)
    {
        int rvalue=rand()%2;
        if(rvalue==0)
        {
            if(dbc.login(username,password)!=true)
            {
                if(dbc.login(username,password)!=true)
                {
                    cout<<"DB Failure 2nd Times"<<endl; return -1;
                }
            }
            else
            {
                cout<<"DB Success"<<endl; return 1;
            }
        }
        else
        {
            return dbc.login2(username,password);
        }
    }
};
TEST(MyDatabase,logintest)
{
    //Arrange
    MockDB mdb;
    MyDatabase db(mdb);
    ON_CALL(mdb,login(_,_)).
    WillByDefault(Return(true));
    ON_CALL(mdb,login2(_,_)).
    WillByDefault(Return(true));
    // EXPECT_CALL(mdb,login(_,_))
    // .Times(2).
    // WillRepeatedly(Return(false));//WillOnce(Return(true));
    //Act
    int RetVal= db.Init("Terminator","I'll be back");
    //Assert
    EXPECT_EQ(RetVal,1);
}
int main(int argc, char**argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
