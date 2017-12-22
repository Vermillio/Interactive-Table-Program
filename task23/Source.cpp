//This program interactively creates a table that, in turn (also in interactive mode) can: 1 Create, add, delete columns, rows and cells 2 Read and write to a file 3 Edit columns. 
//Columns can have types: integer , short, char, string, double, bool. 
//Types can be changed and transformed if possible, i.e. those that are possible. For example, short to integer.

#include "Table.h"

using namespace std;

int main()
{
	Table T;
	T.demo();
	system("pause");
	return 0;
}