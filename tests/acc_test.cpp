#include <string>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Transaction.h"
#include "Account.h"
using ::testing::_;

class MockTransaction : public Transaction {
public:
	MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

class MockAccount : public Account {
public:
	MockAccount(int id, int balance) : Account(id, balance) {};
	MOCK_METHOD(int, GetBalance, (), (const, override));
	MOCK_METHOD(void, ChangeBalance, (int diff), (override));
	MOCK_METHOD(void, Lock, (), (override));
	MOCK_METHOD(void, Unlock, (), (override));
	MOCK_METHOD(int, id, (), (const));
};

TEST(Transaction_test, test_set_fee) {
	Transaction trans;
	trans.set_fee(5);
	EXPECT_TRUE(5 == trans.fee());
}

TEST(MockTransaction_test, test_SaveToDataBase)
{
	Account acc1(1, 200);
	Account acc2(2, 873);
	MockTransaction trans;
	EXPECT_CALL(trans, SaveToDataBase(_, _, _)).Times(1);	 
	trans.SaveToDataBase(acc1, acc2, 150);
	std::cout << acc1.id() << "\nÃÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÉÄÀ\n";
	std::cout << acc1.GetBalance() << "\nÃÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÉÄÀ\n";
	std::cout << acc2.id() << "\nÃÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÉÄÀ\n";
	std::cout << acc2.GetBalance() << "\nÃÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÉÄÀ\n";
}

TEST(Transaction_test, test_Make) 
{
	Account acc1(1, 200);
	Account acc2(2, 873);
	Transaction trans;
	bool succes = trans.Make(acc1, acc2, 150);
	std::cout << trans.fee();
	EXPECT_TRUE(acc1.GetBalance() == (50 - trans.fee()));
}

TEST(Account_test, test_GetBalance1)
{
	Account acc(101, 1337);

	int balance = acc.GetBalance();

	EXPECT_EQ(balance, 1337);
	//EXPECT_EQ(balance, 1003);
	//EXPECT_TRUE(Acc.GetBalance() == 999);
	//EXPECT_CALL(Acc, GetBalance());
}

TEST(Account_test, test_GetBalance2) 
{
	Account acc(99, 0);// Arrange

	int balance = acc.GetBalance();//Act

	EXPECT_EQ(balance, 0);//Assert
}

TEST(Account_test, test_ChangeBalance)
{
	Account acc(99, 1);

	acc.Lock();
	acc.ChangeBalance(87556);
	acc.Unlock();
	int balance = acc.GetBalance();

	EXPECT_EQ(balance, 87557);
}

TEST(Account_test, test_Lock) 
{
	Account acc(99, 0);

	ASSERT_ANY_THROW(acc.ChangeBalance(87556));
}

TEST(Account_test, test_Lock2)
{
	Account acc(99, 0);

	acc.Lock();
	
	ASSERT_ANY_THROW(acc.Lock(););
}

TEST(Account_test, test_UnLock)
{
	Account acc(99, 0);

	acc.Lock();
	acc.Unlock();
	ASSERT_NO_THROW(acc.Lock());
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

