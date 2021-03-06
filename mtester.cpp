#include "table.h"
#include <cstdlib> /* srand, rand */
#include <time.h>  /* time */

//Tester
using namespace std;
int main()
{
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

		//table.print();
		cout << endl;
		table.update("k999", 5);
		//table.print();
		cout << endl;
		table.update("k999", 9);
#ifdef _DEBUG
		table.print();
#endif
		cout << "Here should do remove." << endl;
		if (table.remove("k999"))
		{
			cout << "Removal of k999 successfully completed" << endl;
		}
		else
		{
			cout << "Removal of k999 failed" << endl;
		}
#ifdef _DEBUG
		table.print();
#endif
		cout << endl;
		try
		{
			ChainingTable<int> c0 = ChainingTable<int>(0, 0);
			cout << " test copy assigment" << endl;
			c0 = table;
#ifdef _DEBUG
			c0.print();
#endif
			cout << " test move assigment" << endl;
			ChainingTable<int> c1 = std::move(c0);
			cout << " test c1 to see if it has c0 data" << endl;
#ifdef _DEBUG
			c1.print();
#endif
			//c0 can't be print, function break here
			cout << " test c0 to see if it is empty" << endl;
//table.print();
#ifdef _DEBUG
			c0.print();
#endif
		}
		catch (string str)
		{
			cout << str << endl;
		}
		catch (const char *str)
		{
			cout << str << endl;
		}

		ChainingTable<int> table2(10, 1.5);
		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = i * 20; j < (i + 1) * 20; j++)
			{
				table2.update(string("k") + to_string(j), j);
			}
			for (size_t j = i * 20; j < (i + 1) * 20; j++)
			{
				int temp = -1;
				if (!table2.find(string("k") + to_string(j), temp) || temp != j)
				{
					cout << "Incorrect Result!!!" << endl;
					exit(0);
				}
			}
		}
		for (size_t j = 0; j < 200; j++)
		{
			int temp = -1;
			if (!table2.find(string("k") + to_string(j), temp) || temp != j)
			{
				cout << "Incorrect Result!!!" << endl;
				exit(0);
			}
		}

#ifdef _DEBUG
		table2.print();
#endif
	}

	srand(time(0));
	cout << "Memory leak test:" << endl;
	cout << "Monitoring memory usage of the program while the program is running to check memory leak" << endl;
	cout << "To debug memory leak, use an environment that is able to profile heap" << endl;
	for (size_t i = 0; i < 20; i++)
	{
		cout << "Constructors and destructor" << endl;
		for (size_t i = 0; i < 100; i++)
		{
			ChainingTable<int> t = ChainingTable<int>(50, 1.2);
			for (size_t j = 0; j < 100; j++)
			{
				t.update(string("k") + to_string(j), j);
			}
#ifdef _DEBUG
			t.print();
#endif
			for (size_t j = 0; j < 100; j++)
			{
				t.update(string("k") + to_string(j), j + 2);
			}
#ifdef _DEBUG
			t.print();
#endif
			for (size_t j = 0; j < 200; j++)
			{
				int k = rand() % 1000;
				t.update(string("k") + to_string(k), k + k);
			}
			ChainingTable<int> t1 = t;
			for (size_t j = 0; j < 200; j++)
			{
				int k = rand() % 1000;
				t1.update(string("k") + to_string(k), k + k);
			}

			try
			{
				ChainingTable<int> t2 = std::move(t);

				for (size_t j = 0; j < 200; j++)
				{
					int k = rand() % 1000;
					t1.update(string("k") + to_string(k), k + k);
				}
				for (size_t j = 0; j < 200; j++)
				{
					int k = rand() % 1000;
					t2.update(string("k") + to_string(k), k + k);
				}
				for (size_t j = 0; j < 200; j++)
				{
					int k = rand() % 1000;
					t.update(string("k") + to_string(k), k + k);
				}
			}
			catch (string str)
			{
				cout << str << endl;
			}
			catch (const char *str)
			{
				cout << str << endl;
			}
		}
		cout << "Constructor and destructor tested" << endl;
		cout << "copy assignment operator" << endl;
		for (size_t i = 0; i < 100; i++)
		{
			ChainingTable<int> t = ChainingTable<int>(50, 0.5);
			for (size_t j = 0; j < 1000; j++)
			{
				t.update(string("k") + to_string(j), j);
			}
			ChainingTable<int> t1 = ChainingTable<int>(100, 0.5);
			for (size_t j = 0; j < 1000; j++)
			{
				t1.update(string("k") + to_string(j), j);
			}
			t1 = t;
			for (size_t j = 0; j < 1000; j++)
			{
				t.update(string("k") + to_string(j), j);
			}
		}
		cout << "copy assignment operator tested" << endl;
		cout << "move assignment operator" << endl;
		for (size_t i = 0; i < 100; i++)
		{
			ChainingTable<int> t = ChainingTable<int>(50, 1.2);
			for (size_t j = 0; j < 1000; j++)
			{
				t.update(string("k") + to_string(j), j);
			}
			ChainingTable<int> t1 = ChainingTable<int>(100, 1.5);
			for (size_t j = 0; j < 1000; j++)
			{
				t1.update(string("k") + to_string(j), j);
			}
			try
			{
				t1 = std::move(t);
				for (size_t j = 0; j < 1000; j++)
				{
					t.update(string("k") + to_string(j), j);
				}
				for (size_t j = 0; j < 1000; j++)
				{
					t1.update(string("k") + to_string(j), j);
				}
			}
			catch (string str)
			{
				cout << str << endl;
			}
			catch (const char *str)
			{
				cout << str << endl;
			}
		}
		cout << "move assignment operator tested" << endl;
	}
	return 0;
}