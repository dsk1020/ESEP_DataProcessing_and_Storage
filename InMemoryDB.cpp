#include "InMemoryDB.h"

#include <iostream>


using std::cout;
using std::endl;
using std::string;

InMemoryDb::InMemoryDb() {}
void InMemoryDb::begin_transaction()
{
    try
    {
        if(activeTransaction)
        {
            throw exception();
        }
    }catch(exception& e)
    {
        cout << "An exception occurred: ACTIVE TRANSACTION - COMMIT OR ROLLBACK FOR NEW TRANSACTION \n";
        return;
    }

    activeChanges = new Transaction();
    activeTransaction = true;
}

void InMemoryDb::commit()
{
    try
    {
        if(!activeTransaction)
        {
            throw exception();
        }
    }catch(exception& e)
    {
        cout << "An exception occurred: NO ACTIVE TRANSACTION TO COMMIT\n";
        return;
    }

    activeChanges->writeChanges(database);

    delete activeChanges;
    activeChanges = nullptr;
    activeTransaction = false;
}

void InMemoryDb::rollback()
{
    try
    {
        if(!activeTransaction)
        {
            throw exception();
        }
    }catch(exception& e)
    {
        cout << "An exception occurred: NO ACTIVE TRANSACTION TO ROLLBACK\n";
        return;
    }

    delete activeChanges;
    activeChanges = nullptr;
    activeTransaction = false;
}

int InMemoryDb::get(string key)
{
    auto iter = database.find(key);
    if(iter == database.end())
    {
        return NULL;
    }
    return iter->second;
}

void InMemoryDb::put(string key, int val)
{
    try
    {
        if(!activeTransaction)
        {
            throw exception();
        }
    }catch(exception& e)
    {
        cout << "An exception occurred: NO ACTIVE TRANSACTION TO PUT CHANGES\n";
        return;
    }

    activeChanges->addChange(key, val);
}
