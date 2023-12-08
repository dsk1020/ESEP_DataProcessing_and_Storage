#include <string>
#include "InMemoryDB.h"
#include "gtest/gtest.h"

using std::string;

string ROLLBACK = "An exception occurred: NO ACTIVE TRANSACTION TO ROLLBACK\n";
string COMMIT = "An exception occurred: NO ACTIVE TRANSACTION TO COMMIT\n";
string PUT = "An exception occurred: NO ACTIVE TRANSACTION TO PUT CHANGES\n";
string TRANSACTION = "An exception occurred: ACTIVE TRANSACTION - COMMIT OR ROLLBACK FOR NEW TRANSACTION \n";

TEST(Exceptions, rollBack)
{
    InMemoryDb inmemoryDB;
    testing::internal::CaptureStdout();
    inmemoryDB.rollback();
    string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, ROLLBACK);

}
TEST(Exceptions, commit)
{
    InMemoryDb inmemoryDB;
    testing::internal::CaptureStdout();
    inmemoryDB.commit();
    string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, COMMIT);
}
TEST(Exceptions, put)
{
    InMemoryDb inmemoryDB;
    testing::internal::CaptureStdout();
    inmemoryDB.put("CIS", 4930);
    string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, PUT);
}
TEST(Exceptions, transaction)
{
    InMemoryDb inmemoryDB;
    inmemoryDB.begin_transaction();

    testing::internal::CaptureStdout();
    inmemoryDB.begin_transaction();
    string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, TRANSACTION);
}

TEST(unitFunctionality, rollback)
{
    InMemoryDb inmemoryDB;
    inmemoryDB.begin_transaction();

    inmemoryDB.put("a", 10);
    inmemoryDB.put("b", 20);
    inmemoryDB.put("c", 30);

    inmemoryDB.rollback();

    ASSERT_EQ(inmemoryDB.get("a"), NULL);
    ASSERT_EQ(inmemoryDB.get("b"), NULL);
    ASSERT_EQ(inmemoryDB.get("c"), NULL);
}
TEST(unitFunctionality, commi)
{
    InMemoryDb inmemoryDB;
    inmemoryDB.begin_transaction();

    inmemoryDB.put("a", 10);
    inmemoryDB.put("b", 20);
    inmemoryDB.put("c", 30);

    inmemoryDB.commit();

    ASSERT_EQ(inmemoryDB.get("a"), 10);
    ASSERT_EQ(inmemoryDB.get("b"), 20);
    ASSERT_EQ(inmemoryDB.get("c"), 30);
}
TEST(unitFunctionality, getNULL)
{
    InMemoryDb inmemoryDB;

    ASSERT_EQ(inmemoryDB.get("a"), NULL);

    inmemoryDB.begin_transaction();
    inmemoryDB.put("a", 10);

    ASSERT_EQ(inmemoryDB.get("a"), NULL);

    inmemoryDB.rollback();

    ASSERT_EQ(inmemoryDB.get("a"), NULL);
}
TEST(unitFunctionality, get)
{
    InMemoryDb inmemoryDB;

    inmemoryDB.begin_transaction();
    inmemoryDB.put("a", 10);
    inmemoryDB.commit();

    ASSERT_EQ(inmemoryDB.get("a"), 10);

    inmemoryDB.begin_transaction();
    inmemoryDB.put("b", 11);
    inmemoryDB.commit();

    ASSERT_EQ(inmemoryDB.get("b"), 11);

    inmemoryDB.begin_transaction();
    inmemoryDB.put("a", 111111111);
    inmemoryDB.commit();

    ASSERT_EQ(inmemoryDB.get("a"), 111111111);
}

TEST(LargeTests, Provided_Case)
{
    // --- TEST CASE from assignment --- //
    InMemoryDb inmemoryDB;

    ASSERT_EQ(inmemoryDB.get("A"), NULL); // should return null, because A doesn’t exist in the DB yet

    testing::internal::CaptureStdout();
    inmemoryDB.put("A", 5); // should throw an error because a transaction is not in progress
    string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, PUT);

    inmemoryDB.begin_transaction(); // starts a new transaction

    inmemoryDB.put("A", 5); // set’s value of A to 5, but its not committed yet

    ASSERT_EQ(inmemoryDB.get("A"), NULL); // should return null, because updates to A are not committed yet

    inmemoryDB.put("A", 6); // update A’s value to 6 within the transaction

    inmemoryDB.commit(); // commits the open transaction

    ASSERT_EQ(inmemoryDB.get("A"), 6);

    testing::internal::CaptureStdout();
    inmemoryDB.commit(); // throws an error, because there is no open transaction
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, COMMIT);

    testing::internal::CaptureStdout();
    inmemoryDB.rollback(); // throws an error because there is no ongoing transaction
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, ROLLBACK);

    ASSERT_EQ(inmemoryDB.get("B"), NULL); // should return null because B does not exist in the database

    inmemoryDB.begin_transaction(); // starts a new transaction
    inmemoryDB.put("B", 10); // Set key B’s value to 10 within the transaction
    inmemoryDB.rollback(); // Rollback the transaction - revert any changes made to B

    ASSERT_EQ(inmemoryDB.get("B"), NULL); // Should return null because changes to B were rolled back
}

TEST(LargeTests, Multi_Put)
{
    InMemoryDb inmemoryDB;

    inmemoryDB.begin_transaction(); // starts a new transaction

    inmemoryDB.put("Alpha", 2);
    inmemoryDB.put("Bravo", 4);
    inmemoryDB.put("Charlie", 6);
    inmemoryDB.put("Delta", 8);
    inmemoryDB.put("Echo", 10);
    inmemoryDB.put("Foxtrot", 12);
    inmemoryDB.put("Golf", 14);
    inmemoryDB.put("Hotel", 16);
    inmemoryDB.put("India", 18);
    inmemoryDB.put("Juliet", 20);
    inmemoryDB.put("Kilo", 22);
    inmemoryDB.put("Lima", 24);
    inmemoryDB.put("Mike", 26);
    inmemoryDB.put("November", 1);
    inmemoryDB.put("Oscar", 3);
    inmemoryDB.put("Papa", 5);
    inmemoryDB.put("Quebec", 7);
    inmemoryDB.put("Romeo", 9);
    inmemoryDB.put("Sierra", 11);
    inmemoryDB.put("Tango", 13);
    inmemoryDB.put("Uniform", 15);
    inmemoryDB.put("Victor", 19);
    inmemoryDB.put("Whiskey", 21);
    inmemoryDB.put("X-Ray", 23);
    inmemoryDB.put("Yankee", 25);
    inmemoryDB.put("Zulu", 27);

    inmemoryDB.commit();

    ASSERT_EQ(inmemoryDB.get("Echo"), 10);
    ASSERT_EQ(inmemoryDB.get("November"), 1);
    ASSERT_EQ(inmemoryDB.get("Delta"), 8);
    ASSERT_EQ(inmemoryDB.get("Oscar"), 3);
    ASSERT_EQ(inmemoryDB.get("Sierra"), 11);

    inmemoryDB.begin_transaction();

    inmemoryDB.put("Echo", 100);
    inmemoryDB.put("Sierra", 100);
    inmemoryDB.put("Echo", 200);
    inmemoryDB.put("Papa", 100);

    inmemoryDB.commit();

    ASSERT_EQ(inmemoryDB.get("Echo"), 200);
    ASSERT_EQ(inmemoryDB.get("Sierra"), 100);
    ASSERT_EQ(inmemoryDB.get("Papa"), 100);

    inmemoryDB.begin_transaction();

    inmemoryDB.put("Echo", 10);
    inmemoryDB.put("Sierra", 11);

    inmemoryDB.rollback();

    ASSERT_EQ(inmemoryDB.get("Echo"), 200);
    ASSERT_EQ(inmemoryDB.get("Sierra"), 100);

}