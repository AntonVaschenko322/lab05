#include <string>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
//#include "googletest/googletest/include/gtest/gtest.h"
//#include "googletest/googlemock/include/gmock/gmock.h"
#include "Transaction.h"
#include "Account.h"
using ::testing::_;

class MockTransaction : public Transaction {
//class MockTransaction {
public:
	//MockTransaction() : Transaction() {};
	//MOCK_METHOD(bool, Make, (Account& from, Account& to, int sum), ());
	//MOCK_METHOD(void, Credit, (Account& accout, int sum), ());
	//MOCK_METHOD(bool, Debit, (Account& accout, int sum), ());
	//MOCK_METHOD(int, fee, (), (const));
	//MOCK_METHOD(void, set_fee, (int fee));
	MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

class MockAccount : public Account {
public:
	MockAccount(int id, int balance) : Account(id, balance) {};
	//~MockAccount()
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

TEST(Transaction_test, test_Make) {
	//MockAccount acc1(1, 100);
	//MockAccount acc2(2, 873);
	Account acc1(1, 200);
	Account acc2(2, 873);
	Transaction trans;
	//EXPECT_TRUE(Acc.GetBalance() == 999);
	//EXPECT_CALL(acc1, GetBalance()).Times(1);
	//EXPECT_CALL(trans, SaveToDataBase(_, _, _)).Times(1);
	bool succes = trans.Make(acc1, acc2, 150);
	//std::cout << trans.fee();
	//EXPECT_TRUE(succes);
	EXPECT_TRUE(acc1.GetBalance() == (50 - trans.fee()));
}

TEST(MockTransaction_test, test_SaveToDataBase) {
	/*MockAccount acc1(1, 100);
	MockAccount acc2(2, 873);*/
	Account acc1(1, 200);
	Account acc2(2, 873);
	//::testing::NiceMock<MockTransaction> trans;
	MockTransaction trans;
	//EXPECT_TRUE(Acc.GetBalance() == 999);
	//EXPECT_CALL(acc1, GetBalance()).Times(1);
	// 
	//bool succes = trans.Make(acc1, acc2, 150);
	//EXPECT_TRUE(succes);

	//EXPECT_CALL(trans, Make(_, _, _)).Times(1);
	// 
	EXPECT_CALL(trans, SaveToDataBase(_, _, _)).Times(1);

	//EXPECT_CALL(acc1, GetBalance()).Times(3);
	//Transaction trans;
	//EXPECT_CALL(acc1, Lock()).Times(testing::AnyNumber());
	/*EXPECT_CALL(trans, Make(_, _, _)).Times(1);
	EXPECT_CALL(trans, Credit(_, _)).Times(1);*/

	//bool succes = trans.Make(acc1, acc2, 150);
	//EXPECT_TRUE(succes);
	 
	trans.SaveToDataBase(acc1, acc2, 150);

	//EXPECT_CALL(trans, fee).Times(1);

	//int comis = trans.fee();
	std::cout << acc1.id() << "\nÃÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÉÄÀ\n";
	std::cout << acc1.GetBalance() << "\nÃÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÉÄÀ\n";
	std::cout << acc2.id() << "\nÃÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÉÄÀ\n";
	std::cout << acc2.GetBalance() << "\nÃÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÎÉÄÀ\n";
}

TEST(Account_test, test_GetBalance1) {
	Account acc(101, 1337);

	int balance = acc.GetBalance();

	EXPECT_EQ(balance, 1337);
	//EXPECT_EQ(balance, 1003);
	//EXPECT_TRUE(Acc.GetBalance() == 999);
	//EXPECT_CALL(Acc, GetBalance());
}

TEST(Account_test, test_GetBalance2) {
	Account acc(99, 0);// Arrange

	int balance = acc.GetBalance();//Act

	EXPECT_EQ(balance, 0);//Assert
}

TEST(Account_test, test_ChangeBalance) {
	Account acc(99, 1);

	acc.Lock();
	acc.ChangeBalance(87556);
	acc.Unlock();
	int balance = acc.GetBalance();

	EXPECT_EQ(balance, 87557);
}

TEST(Account_test, test_Lock) {
	Account acc(99, 0);

	ASSERT_ANY_THROW(acc.ChangeBalance(87556));
}

TEST(Account_test, test_Lock2) {
	Account acc(99, 0);

	acc.Lock();
	
	ASSERT_ANY_THROW(acc.Lock(););
}

TEST(Account_test, test_UnLock) {
	Account acc(99, 0);

	acc.Lock();
	acc.Unlock();
	ASSERT_NO_THROW(acc.Lock());
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

