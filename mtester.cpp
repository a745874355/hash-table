#include "table.h"
//Tester
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
		c0.print();
#endif		

	}

	return 0;
}