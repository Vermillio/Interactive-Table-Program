#include "Table.h"
#include <iostream>
#include <fstream>


using namespace std;

void Table::inputConsole()
{
//	data.clear();
	int r, c;
	cout << "Table rows : ";
	cin >> r;
	cout << "Table columns : ";
	cin >> c;
	data.resize(c);
	for (int i = 0; i < c; ++i)
	{
		data[i].resize(r);
		cout << "Column data : ";
		for (int j = 0; j < r; ++j)
		{
			cin >> data[i][j];
			if (data[i][j].size() > lenmax)
				lenmax = data[i][j].size();
		}
		cout << "Column #" << c << " type : ";
		cin >> data[i].type;
		if (!checkType(i, data[i].type))
		{
			clear();
			return;
		}
	}
}

void Table::writeFile(string filename)
{
	ofstream fout(filename, ios::out | ios::binary | ios::trunc);
	if (!fout.is_open())
	{
		cout << "Cannot open " << filename << endl;
		return;
 	}
	int r = rows();
	int c = columns();
	fout.write((char*)&c, sizeof(int));
	fout.write((char*)&r, sizeof(int));
	for (size_t i = 0; i < columns(); ++i)
	{
		fout.write((char*)&data[i].type, sizeof(int));
		for (size_t j = 0; j < rows(); ++j)
		{
			int sz = sizeof(data[i].data[j]);
			fout.write((char*)&sz, sizeof(int));
			fout.write((char*)&data[i].data[j], sz);
		}
	}
	fout.close();
}

void Table::readFile(string filename)
{
	data.clear();
	lenmax = 0;
	ifstream fin(filename, ios::in | ios::binary);
	if (!fin.is_open())
	{
		cout << "Cannot open " << filename << endl;
		return;
	}
	int sz, r, c;
	fin.read((char*)&c, sizeof(int));
	fin.read((char*)&r, sizeof(int));
	for (int k = 0; k < c; ++k)
	{
		data.push_back(column());
		fin.read((char*)&data[k].type, sizeof(int));
		data[k].resize(r);
		for (int i = 0; i < r; ++i)
		{
			fin.read((char*)&sz, sizeof(int));
			fin.read((char*)&data[k].data[i], sz);
			if (data[k][i].size() > lenmax)
				lenmax = data[k][i].size();
		}
	}
	fin.close();
}

void Table::clear()
{
	data.clear();
	lenmax = 0;
}

void Table::demo()
{
	bool toexit = false;
	int choise1, choise2;

	
	while (toexit == false)
	{
		system("cls");
		cout << *this;
		cout << "0 - INPUT, 1 - EDIT, 2 - OUTPUT, default - EXIT" << endl;
		cout << ">>>";
		cin >> choise1;
		if (choise1 == 0)
		{
			cout << "	0 - CONSOLE, 1 - RANDOM, 2 - READ FILE, default - CANCEL" << endl;
			cout << "	>>>";
			cin >> choise2;
			if (choise2 == 0)
			{
				inputConsole();
			}
			else if (choise2 == 1)
			{
				unsigned int r, c, maxlen;
				cout << "	rows >>>";
				cin >> r;
				cout << "	columns >>>";
				cin >> c;
				cout << "	max length >>>";
				cin >> maxlen;
				createRandom(r, c, maxlen);
			}
			else if (choise2 == 2)
			{
				string filename;
				cout << "	filename >>>";
				cin.ignore(cin.rdbuf()->in_avail());
				getline(cin, filename);
				readFile(filename);
			}
		}
		else if (choise1 == 1)
		{
			cout << "	0 - ADD COLUMN, 1 - ADD ROW, 2 - REMOVE COLUMN, 3 - REMOVE ROW, 4 - EDIT VALUE, 5 - EDIT ROW, 6 - EDIT COLUMN, default - CANCEL" << endl;
			cout << "	>>>";
			cin >> choise2;
			switch (choise2)
			{
			case 0:
			{
				cout << "	ADD COLUMN" << endl;
				int pos;
				cout << "	position >>>";
				cin >> pos;
				int type;
				cout << "	column type >>>";
				cin >> type;
				addColumn(pos, type);
				break;
			}
			case 1:
			{
				cout << "	ADD ROW" << endl;
				int pos;
				cout << "	position >>>";
				cin >> pos;
				addRow(pos);
				break;
			}
			case 2:
			{
				cout << "	REMOVE COLUMN" << endl;
				bool success;
				int pos;
				cout << "	position >>>";
				cin >> pos;
				removeColumn(pos, success);
				if (success)
					cout << "	success." << endl;
				else cout << "	error." << endl;
				break;
			}
			case 3:
			{
				cout << "	REMOVE ROW" << endl;
				bool success;
				int pos;
				cout << "	position >>>";
				cin >> pos;
				removeRow(pos, success);
				if (success)
					cout << "	success." << endl;
				else cout << "	error occured." << endl;
				break;
			}
			case 4:
			{
				cout << "	EDIT VALUE" << endl;
				bool success;
				int r, c;
				cout << "	Row >>>";
				cin >> r;
				cout << "	Column >>>";
				cin >> c;
				string value;
				cout << "	Value >>>";

				cin.ignore(cin.rdbuf()->in_avail());
				getline(cin, value);
				cin.ignore(cin.rdbuf()->in_avail());

				setValue(r, c, value, success);
				if (success)
					cout << "	success." << endl;
				else cout << "	error occured." << endl;
				break;
			}
			case 5:
			{
				cout << "	EDIT ROW" << endl;
				cout << "	position >>>";
				int pos;
				cin >> pos;
				cout << "	enter new row" << endl;
				vector<string> newrow(columns());
				for (int i = 0; i < columns(); ++i)
				{
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "	>>>";
					getline(cin, newrow[i]);
					if (newrow[i].size() > lenmax)
						lenmax = newrow[i].size();
				}
				bool success;
				setRow(pos, newrow, success);
				if (success)
					cout << "	success." << endl;
				else cout << "	error." << endl;
				break;
			}
			case 6:
			{
				cout << "	EDIT COLUMN" << endl;
				cout << "	position >>>";
				int pos;
				cin >> pos;
				cout << "	enter new column" << endl;
				vector<string> newcol(rows());
				for (int i = 0; i < rows(); ++i)
				{
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "	>>>";
					getline(cin, newcol[i]);
					if (newcol[i].size() > lenmax)
						lenmax = newcol[i].size();
				}
				int type;
				cout << "	type >>>";
				cin >> type;
				bool success;
				setColumn(pos, type, newcol, success);
				if (success)
					cout << "	success." << endl;
				else cout << "	error." << endl;
				break;
			}
			default:
				break;
			}

		}
		else if (choise1 == 2)
		{
			cout << "	0 - WRITE FILE, default - CANCEL" << endl;
			cout << "	>>>";
			cin >> choise2;

			if (choise2 == 0)
			{
				string filename;
				cout << "	filename : ";
				cin >> filename;
				writeFile(filename);
			}
		}
		else
			toexit = true;
	}
	clear();
}

column & Table::operator[](int index)
{
	return data[index];
}

ostream & operator<<(ostream & c, Table &T)
{
	for (int i = 0; i < T.columns() * T.lenmax + 3*T.columns(); ++i)
	{
		c << "_";
	}
	cout << endl;
	for (int i = 0; i < T.rows(); ++i)
	{
		c << "|";
		for (int j = 0; j < T.columns(); ++j)
		{
			c << string(T.lenmax - T[j][i].size() + 1, ' ');
			c << T[j][i] << " |";
		}
		c << endl;
	}
	for (int i = 0; i < T.columns() * T.lenmax + 3*T.columns(); ++i)
	{
		c << "_";
	}
	cout << endl;
	return c;
}

//UNFINISHED
bool Table::checkType(int column, int type)
{
	switch (type)
	{
	case 0:
		for (auto it : data[column].data)
		{
			if (it != "1" && it != "0")
			{
				return false;
			}
		}
		break;
	case 1:
		for (auto it : data[column].data)
		{
			if (it.size() != 1)
			{
				return false;
			}
		}
		break;
	case 2:
		for (auto it : data[column].data)
		{
			if (it.size() != 1)
			{
				return false;
			}
		}
		break;
	case 3:
	{
		int shortmax = 32767;
		for (auto it : data[column].data)
		{
			if (it.size() > 5)
			{
				return false;
			}
		}
		break;
	}
	case 4:
	{
		int intmax = 2147483647;
		for (auto it : data[column].data)
		{
			if (it.size() != 1)
			{
				return false;
			}
		}
		break;
	}
	default:
		break;
	}
	return true;
}

int Table::rows()
{
	return data.size()>0 ? data[0].size() : 0;
}

int Table::columns()
{
	return data.size();
}

void Table::getSize(int & rows, int & columns)
{
	columns = data.size();
	if (columns != 0)
		rows = data[0].size();
	else rows = 0;
}

void Table::createRandom(int r, int c, int maxlen)
{
	data.resize(c);
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < c; ++i)
	{
		data[i].type = rand() % 6;
		data[i].resize(r);
		for (int j = 0; j < r; ++j)
		{
			int strsize = rand() % (maxlen+1);
			if (strsize > lenmax)
				lenmax = strsize;
			data[i][j].resize(strsize);
			for (int k = 0; k < strsize; ++k)
				data[i][j][k] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
	}
}

void Table::addColumn(int pos, int type)
{
	if (pos < 1)
		return;
	--pos;
	if (pos > columns())
		data.resize(pos);
	if (pos == columns())
		data.push_back(column(type, vector<string>(rows())));
	else
		data.insert( data.begin() + pos-1, column( type, vector<string>(rows()) ) );
}

void Table::addRow(int pos)
{
	if (pos < 1)
		return;
	--pos;
	if (pos > rows())
		for (int i = 0; i < columns(); ++i)
			data[i].resize(pos);

	if (pos == rows())
		for (int i = 0; i < columns(); ++i)
			data[i].data.push_back("");
	else	
		for (int i = 0; i < columns(); ++i)
			data[i].data.insert(data[i].data.begin() + pos, "");
}

void Table::removeColumn(int pos, bool &success)
{
	if (pos<1 || pos > data.size())
	{
		success = false;
		return;
	}
	else success = true;
	data.erase(data.begin() + pos-1);
}

void Table::removeRow(int pos, bool &success)
{
	if (pos<1 || data.size() == 0 || pos > data[0].size())
	{
		success = false;
		return;
	}
	else success = true;
	for (int i = 0; i < data.size(); ++i)
	{
		data[i].data.erase(data[i].data.begin() + pos-1);
	}
}

void Table::setValue(int row, int column, string newValue, bool & success)
{
	if (column < 1 || row < 1 || column > data.size() || row > data[0].size())
	{
		success = false;
		return;
	}
	success = true;
	data[column-1][row-1] = newValue;
	if (newValue.size() > lenmax)
		lenmax = newValue.size();
}


//-
void Table::setRow(int pos, vector<string> &_data, bool &success)
{
	if (pos < 1)
	{
		success = false;
		return;
	}
	_data.resize(columns());
	for (int i = 0; i < columns(); ++i)
		data[i][pos - 1] = _data[i];
	success = true;
}

void Table::setColumn(int pos, int type, vector<string> &_data, bool &success)
{
	if (pos < 1)
	{
		success = false;
		return;
	}
	_data.resize(rows());
	data[pos-1] = column(type, _data);
	success = true;
}
//-


void Table::setType(int column, int type, bool &success)
{
	if (column < 1)
		return;
	--column;
	if (type < 0 || type > 5)
	{
		success = false;
		return;
	}
	if (data[column].type < type)
	{
		data[column].type = type;
		return;
	}

	if (!checkType(column, type))
	{
		success = false;
		return;
	}
	success = true;
	data[column].type = type;
	return;
}
