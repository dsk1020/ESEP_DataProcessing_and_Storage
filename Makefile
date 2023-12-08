test.out: test.out InMemoryDB.h InMemoryDB.cpp
	g++ -std=c++17 -o test.out InMemoryDB.cpp test.cpp -lgtest -lgtest_main -lpthread
direct.out: InMemoryDB.h InMemoryDB.cpp main.cpp
	g++ -std=c++17 -o direct.out main.cpp InMemoryDB.cpp