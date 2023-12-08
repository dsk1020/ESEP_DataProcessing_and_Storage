#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::vector;
using std::exception;

struct Transaction
{
    map<string, int> changes;
public:
    Transaction(){}

   void writeChanges(map<string,int>& db)
    {
        for(auto iter = changes.begin(); iter != changes.end(); iter++)
        {
            db[iter->first] = iter->second;
        }
    }

    void addChange(string key, int value)
    {
        changes[key] = value;
    }
};

class InMemoryDb
{
    bool activeTransaction = false;
    Transaction* activeChanges; // stores all changes done to database during a transaction
    map<string, int> database;

public:
    InMemoryDb();
    int get(string key);
    void put(string key, int val);
    void begin_transaction();
    void commit();
    void rollback();

};
