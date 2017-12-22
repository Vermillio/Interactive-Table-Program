#pragma once
#include <vector>
#include <string>

using namespace std;

struct column
{
	int type;
	vector<string> data;

	column() {};
	column(int _type, vector<string> _data) : type(_type), data(_data) {};

	string& operator[] (int index) {
		return data[index];
	}
	void resize(int sz) { data.resize(sz); };
	int size() { return data.size(); };
};

class Table
{
private:
	enum type { tbool, tchar, tshort, tint, tdouble, tstring};
	vector<column> data;
	int lenmax;

	bool checkType(int column, int type);

public:
	int rows();
	int columns();
	void getSize(int &rows, int &columns);
	void inputConsole();
	void createRandom(int r, int c, int maxlen);

	void addColumn(int pos, int type);
	void addRow(int pos);

	void removeColumn(int pos, bool &success);
	void removeRow(int pos, bool &success);

	void setValue(int row, int column, string newValue, bool &success);
	void setRow(int pos, vector<string> &_data, bool &success);
	void setColumn(int pos, int type, vector<string> &_data, bool &success);
	void setType(int column, int newtype, bool &success);

	void writeFile(string filename);
	void readFile(string filename);

	void clear();

	void demo();

	column& operator[] (int index);
	friend ostream& operator<< (ostream& c, Table &T);

	Table() : lenmax(0) {};
};