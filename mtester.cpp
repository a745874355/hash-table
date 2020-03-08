#include "table.h"
#include <cstdlib>     /* srand, rand */
#include <time.h>       /* time */

//Tester
using namespace std;
int main() {
	//for (size_t i = 0; i < 10; i++)
	{

		ChainingTable<int> table(10, 0.7);
#ifdef _DEBUG
		cout << "Table created." << endl;
		table.print();
#endif
		table.update("k123", 1);
		table.update("k456", 1);
		table.update("k789", 1);
		table.update("k888", 3);
		table.update("k997", 5);
		table.update("k998", 5);
		table.update("k996", 5);
		table.update("k995", 5);
	/*	table.update("k994", 5);
		table.update("k993", 5);
		table.update("k992", 5);
		table.update("k991", 5);
		table.update("k990", 5);
		table.update("k989", 5);
		table.update("k988", 5);*/
#ifdef _DEBUG
		//table.print();
		cout << endl;
		table.update("k999", 5);
		//table.print();
		cout << endl;
		table.update("k999", 9);
		table.print();
		cout << "Here should do remove." << endl;
		if (table.remove("k999")) {
			cout << "Removal of k999 successfully completed" << endl;
		}
		else {
			cout << "Removal of k999 failed" << endl;
		}
		table.print();
		cout << endl;
		try{
			ChainingTable<int> c0 = ChainingTable<int>(0,0);
			cout << " test copy assigment" << endl;
			c0 = table;
			c0.print();
			cout << " test move assigment" << endl;
			ChainingTable<int> c1 = std::move(c0);
			cout << " test c1 to see if it has c0 data" << endl;
			c1.print();
			//c0 can't be print, function break here
			cout << " test c0 to see if it is empty" << endl;
			//table.print();
			c0.print();
		}catch(string str){
			cout << str << endl;
		}catch(const char* str){
			cout << str << endl;
		}

#endif		
	}
	srand (time(0));
	cout << "Memory leak test:" << endl;
	cout << "This part should be tested by using an envinronment that is able to profile heap" << endl;
	cout << "Constructors and destructor" << endl;
	for (size_t i = 0; i < 100; i++)
	{
		ChainingTable<int> t = ChainingTable<int>(50, 1.2);
		for(size_t j = 0; j < 100; j++){
			t.update(string("k") + to_string(j), j);
		}
#ifdef _DEBUG
		t.print();
#endif
		for (size_t j = 0; j < 100; j++)
		{
			t.update(string("k") + to_string(j), j+2);
		}
#ifdef _DEBUG
		t.print();
#endif		
		for (size_t j = 0; j < 200; j++){
			int k = rand()%1000;
			t.update(string("k") + to_string(k), k + k);
		}
		ChainingTable<int> t1 = t;
		for (size_t j = 0; j < 200; j++){
			int k = rand()%1000;
			t1.update(string("k") + to_string(k), k + k);
		}

		try{
			ChainingTable<int> t2 = std::move(t);

			for (size_t j = 0; j < 200; j++){
				int k = rand()%1000;
				t1.update(string("k") + to_string(k), k + k);
			}
			for (size_t j = 0; j < 200; j++){
				int k = rand()%1000;
				t2.update(string("k") + to_string(k), k + k);
			}
			for (size_t j = 0; j < 200; j++){
				int k = rand()%1000;
				t.update(string("k") + to_string(k), k + k);
			}
		}catch(string str){
			cout << str << endl;
		}catch(const char* str){
			cout << str << endl;
		}
	}
	cout << "Constructor and destructor tested" << endl;
	cout << "copy assignment operator" << endl;
	for (size_t i = 0; i < 100; i++)
	{
		ChainingTable<int> t = ChainingTable<int>(50, 0.5);
		for(size_t j = 0; j < 1000; j++){
			t.update(string("k") + to_string(j), j);
		}
		ChainingTable<int> t1 = ChainingTable<int>(100, 0.5);
		for(size_t j = 0; j < 1000; j++){
			t1.update(string("k") + to_string(j), j);
		}
		t1 = t;
		for(size_t j = 0; j < 1000; j++){
			t.update(string("k") + to_string(j), j);
		}
	}
	cout << "copy assignment operator tested" << endl;
	cout << "move assignment operator" << endl;
	for (size_t i = 0; i < 100; i++)
	{
		ChainingTable<int> t = ChainingTable<int>(50, 0.5);
		for(size_t j = 0; j < 1000; j++){
			t.update(string("k") + to_string(j), j);
		}
		ChainingTable<int> t1 = ChainingTable<int>(100, 0.5);
		for(size_t j = 0; j < 1000; j++){
			t1.update(string("k") + to_string(j), j);
		}
		try{
			t1 = std::move(t);
			for(size_t j = 0; j < 1000; j++){
				t.update(string("k") + to_string(j), j);
			}
			for(size_t j = 0; j < 1000; j++){
				t1.update(string("k") + to_string(j), j);
			}
		}catch(string str){
			cout << str << endl;
		}catch(const char* str){
			cout << str << endl;
		}

	}
	cout << "move assignment operator tested" << endl;

	

	return 0;
}