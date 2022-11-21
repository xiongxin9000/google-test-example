//2.invoking original and other implementation
//3.setting default action
//4.performing multiple function
#include<gtest/gtest.h>
#include<iostream>
#include<vector>
#include<gmock/gmock.h>

using namespace std;
using testing::AtLeast;
using testing::Return;
using testing::_;
using testing::Invoke;
using testing::InvokeWithoutArgs;
using testing::DoDefault;
using testing::DoAll;
class DataBaseConnect{
public:
    virtual bool login(string username,string password) {cout<<"origin login"<<endl;return true;}
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
            if(dbc.login(username,password)!=true)
            {
                    cout<<"DB Failure 2nd Times"<<endl; return -1;
            }
            else
            {
                cout<<"DB Success"<<endl; return 1;
            }
    }
};
struct testABC
{
    bool dummylogin(string a,string b)
    {
        cout<<"dummy login called"<<endl;
        return true;
    }
};
struct testABC2
{
    void dummylogin(string a,string b)
    {
        cout<<"dummy login called"<<endl;
        return ;
    }
};
bool globalfn()
{
    cout<<"global function called"<<endl;
    return true;
}
TEST(MyDatabase,logintest)
{
    //Arrange
    MockDB mdb;
    MyDatabase db(mdb);
    DataBaseConnect testdb;
    testABC testabc;
    testABC2 testabc2;
    // ON_CALL(mdb,login(_,_)).
    // WillByDefault(Return(true));
    // ON_CALL(mdb,login2(_,_)).
    // WillByDefault(Invoke(&testabc,&testABC::dummylogin));
    // EXPECT_CALL(mdb,login(_,_))
    // .Times(AtLeast(1)).
    // WillOnce(Invoke(&testdb,&DataBaseConnect::login));//WillOnce(Return(true));
    EXPECT_CALL(mdb,login(_,_))
    .Times(AtLeast(1)).
    WillOnce(DoAll(Invoke(&testabc2,&testABC2::dummylogin),Invoke(&testabc2,&testABC2::dummylogin),Return(true)));//WillOnce(Return(true));
    //Act
    // EXPECT_CALL(mdb,login(_,_))
    // .Times(AtLeast(1)).
    // WillOnce(InvokeWithoutArgs(globalfn));//WillOnce(Return(true));
    //Act
    int RetVal= db.Init("Terminator","I'll be back");
    //Assert
    //EXPECT_EQ(RetVal,1);
}
int main(int argc, char**argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
