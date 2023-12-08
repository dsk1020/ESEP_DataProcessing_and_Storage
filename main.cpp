#include <iostream>
#include "InMemoryDB.h"

using std::cout;
using std::endl;

int main() {
    InMemoryDb inmemoryDB;

    inmemoryDB.get("A"); // should return null, because A doesn’t exist in the DB yet
    inmemoryDB.put("A", 5); // should throw an error because a transaction is not in progress
    inmemoryDB.begin_transaction(); // starts a new transaction
    inmemoryDB.put("A", 5); // set’s value of A to 5, but its not committed yet
    inmemoryDB.get("A"); // should return null, because updates to A are not committed yet
    inmemoryDB.put("A", 6); // update A’s value to 6 within the transaction
    inmemoryDB.commit(); // commits the open transaction

    inmemoryDB.get("A"); // should return 6, that was the last value of A to be committed
    inmemoryDB.commit(); // throws an error, because there is no open transaction
    inmemoryDB.rollback(); // throws an error because there is no ongoing transaction
    inmemoryDB.get("B"); // should return null because B does not exist in the database
    inmemoryDB.begin_transaction(); // starts a new transaction
    inmemoryDB.put("B", 10); // Set key B’s value to 10 within the transaction
    inmemoryDB.rollback(); // Rollback the transaction - revert any changes made to B
    inmemoryDB.get("B"); // Should return null because changes to B were rolled back
    return 0;

}
