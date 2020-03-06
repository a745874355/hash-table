#include "table.h"
//Tester
int main(){
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
	table.update("k994", 5);
	table.update("k993", 5);
	table.update("k992", 5);
	table.update("k991", 5);
	table.update("k990", 5);
	table.update("k989", 5);
	table.update("k988", 5);


#ifdef _DEBUG
	table.print();
	cout << endl;
	table.update("k999", 5);
    table.print();
	cout << endl;
	table.update("k999", 9);
	table.print();
	cout << "Here should do remove." << endl;
	table.remove("K999");
	table.print();
	cout << endl;
#endif
	return 0;
}

