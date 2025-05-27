#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"
#include "Transaction.h"

class MockAccount : public Account
{
public:

 MockAccount(int id, int balance) : Account(id, balance) {};
 //~MockAccount()
 MOCK_METHOD(int, GetBalance, (), (const, override));
 MOCK_METHOD(void, ChangeBalance, (int diff), (override));
 MOCK_METHOD(void, Lock, (), (override));
 MOCK_METHOD(void, Unlock, (), (override));
 MOCK_METHOD(int, id, (), (const));
};

class MockTransaction : public Transaction
{
 public:
 MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override)); 
};

TEST(Transaction_test, test_set_fee) {
	Transaction trans;
	trans.set_fee(5);
	EXPECT_TRUE(5 == trans.fee());
}

TEST(trantest, SaveToDataBase)
{
 Account acc1(1, 100);
 Account acc2(2, 873);
 MockTransaction trans;
 EXPECT_CALL(trans, SaveToDataBase(testing::_, testing::_, testing::_)).Times(1);	 
 trans.SaveToDataBase(acc1, acc2, 150);
 std::cout << acc1.id() << "\nÃÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÉÄÀ\n";
 std::cout << acc1.GetBalance() << "\nÃÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÉÄÀ\n";
 std::cout << acc2.id() << "\nÃÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÉÄÀ\n";
 std::cout << acc2.GetBalance() << "\nÃÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÉÄÀ\n";
}

TEST(Transaction_test, test_Make) 
{
 Account ben1(1, 200);
 Account ben2(2, 873);
 Transaction trans;
 bool succes = trans.Make(ben1, ben2, 150);
 EXPECT_TRUE(ben1.GetBalance() == (50 - trans.fee()));
}
 
TEST(acctest, GetBalance)
{
 Account Ben(1092, 357);
 int f = Ben.GetBalance();
 EXPECT_EQ(f, 357);
}

TEST(acctest, ChangeBalance)
{
 Account Ben(1092, 357); 
 Ben.Lock();
 Ben.ChangeBalance(2018);
 EXPECT_EQ(Ben.GetBalance(), 2018+357);
}
TEST(acctest, Lock)
{
 MockAccount Ben(1092, 357);
 Ben.Lock();
 EXPECT_TRUE(Ben.IsLocked());
}

TEST(acctest, unlock)
{
 MockAccount Ben(1092, 357);
 Ben.Unlock();
 EXPECT_EQ(Ben.is_locked_, false);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

