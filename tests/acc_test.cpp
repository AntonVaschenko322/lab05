#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"
#include "Transaction.h"

class MockAccount : public Account
{
public:
 MockAccount(int id, int balance):Account(id, balance){};
 MOCK_METHOD(int, GetBalance, (), (const, override));
 MOCK_METHOD(void, ChangeBalance, (int diff), (override));
 using Account::is_locked_;
 bool IsLocked() const { return is_locked_; }
};

class MockTransaction : public Transaction
{
 public:
 MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override)); 
};

TEST(trantest, SaveToDataBase)
{

 MockAccount acc1(1, 100);
 MockAccount acc2(2, 873);
 MockTransaction trans;
 EXPECT_CALL(trans, SaveToDataBase(testing::_, testing::_, testing::_)).Times(1);	 
 trans.SaveToDataBase(acc1, acc2, 150);
}

 
TEST(acctest, GetBalance)
{
 Account Ben(1092, 357);
 EXPECT_CALL(Ben,  GetBalance()).WillOnce(testing::Return(357)); 
 int f = Ben.GetBalance();
 EXPECT_EQ(f, 357);
}

TEST(acctest, ChangeBalance)
{
 Account Ben(1092, 357);
 EXPECT_CALL(Ben,  GetBalance()).WillOnce(testing::Return(357+2018));
 EXPECT_CALL(Ben,  ChangeBalance(2018)).WillOnce(testing::Return());  
 Ben.Lock();
 Ben.ChangeBalance(2018);
 EXPECT_EQ(Ben.GetBalance(), 2018+357);
}
TEST(acctest, Lock)
{
 Account Ben(1092, 357);
 Ben.Lock();
 EXPECT_TRUE(Ben.IsLocked());
}

TEST(acctest, unlock)
{
 Account Ben(1092, 357);
 Ben.Unlock();
 EXPECT_EQ(Ben.is_locked_, false);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

