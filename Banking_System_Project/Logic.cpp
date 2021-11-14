#include "Logic.h"

void Logic::read_data()
{
	cout << "Enter account number: ";
	cin >> accounts_number;
	cout << "Enter first name: ";
	cin >> first_name;
	cout << "Enter last name: ";
	cin >> last_name;
	cout << "Enter balance: ";
	cin >> total_balance;
	cout << "\n";
}

void Logic::show_data()
{
	cout << "Account number: " << accounts_number << endl;
	cout << "First name: " << first_name << endl;
	cout << "Last name: " << last_name << endl;
	cout << "Current balance: Rs. " << total_balance << endl;
	cout << "------------------------------------------" << endl;
}

void Logic::write_record()
{
	ofstream out_record;
	out_record.open("records.bank", ios::binary | ios::app);
	read_data();
	out_record.write(reinterpret_cast<char*>(this), sizeof(*this));
	out_record.close();
}

void Logic::read_record()
{
	ifstream in_record;
	in_record.open("records.bank", ios::binary | ios::app);
	if (!in_record)
	{
		cout << "Error in Opening Database! File Not Found 404" << endl;
		return;
	}
	cout << "\n****Data from database file****" << endl;
	while (!in_record.eof())
	{
		if (in_record.read(reinterpret_cast<char*>(this), sizeof(*this)))
			show_data();
	}
	in_record.close();
}

void Logic::search_record()
{
	int num;
	ifstream in_record;
	in_record.open("record.bank", ios::binary | ios::app);
	if (!in_record)
	{
		cout << "\nError in openning database! File Not Found 404" << endl;
		return;
	}
	in_record.seekg(0, ios::end);
	int count = in_record.tellg() / sizeof(*this);
	cout << "\nThere are " << count << " records in the file";
	cout << "\nEnter record number to search: ";
	cin >> num;
	in_record.seekg((num - 1) * sizeof(*this));
	in_record.read(reinterpret_cast<char*>(this), sizeof(*this));
	show_data();
}

void Logic::edit_record()
{
	int num = 0;
	fstream io_record;
	io_record.open("record.bank", ios::in | ios::binary);
	if (!io_record)
	{
		cout << "\nError in opening database! File Not Found 404" << endl;
		return;
	}
	io_record.seekg(0, ios::end);
	int count = io_record.tellg() / sizeof(*this);
	cout << "\nThere are " << count << " records in the file";
	cout << "\nEnter record number to edit: ";
	cin >> num;
	io_record.seekg((num - 1) * sizeof(*this));
	io_record.read(reinterpret_cast<char*>(this), sizeof(*this));
	cout << "Record " << num << "has following data" << endl;
	show_data();
	io_record.close();
	io_record.open("record.bank", ios::out | ios::in | ios::binary);
	io_record.seekp((num - 1) * sizeof(*this));
	cout << "\nEnter data to modify " << endl;
	read_data();
	io_record.write(reinterpret_cast<char*>(this), sizeof(*this));
}

void Logic::delete_record()
{
	int num = 0;
	ifstream in_record;
	in_record.open("record.bank", ios::binary);
	if (!in_record)
	{
		cout << "\nError in opening database! File Not Found!" << endl;
		return;
	}
	in_record.seekg(0, ios::end);
	int count = in_record.tellg() / sizeof(*this);
	cout << "\nThere are " << count << " records in the file";
	cout << "\nEnter record number to delete: ";
	cin >> num;
	fstream tmp_file;
	tmp_file.open("tmprecord.bank", ios::out | ios::binary);
	in_record.seekg(0);
	for (int i = 0; i < count; i++)
	{
		in_record.read(reinterpret_cast<char*>(this), sizeof(*this));
		if (i == (num - 1))
			continue;
		tmp_file.write(reinterpret_cast<char*>(this), sizeof(*this));
	}
	in_record.close();
	tmp_file.close();
	remove("record.bank");
	if (!rename("tmprecord.bank", "record.bank"))
	{
		cout << "Error in renaming tmp file to record";
		return;
	}
}

void Logic::Run()
{
	int choice = 0;
	cout << "***Account Information System***" << endl;
	while (true)
	{
		cout << "Select one from options below" << endl;
		cout << "\t1) Add new record" << endl;
		cout << "\t2) Show saved record" << endl;
		cout << "\t3) Search record in saved records" << endl;
		cout << "\t4) Modify record" << endl;
		cout << "\t5) Delete Record" << endl;
		cout << "\t6) Quit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			write_record();
			break;
		case 2:
			read_record();
			break;
		case 3:
			search_record();
			break;
		case 4:
			edit_record();
			break;
		case 5:
			delete_record();
			break;
		case 6:
			exit(0);
			break;
		default:
			cout << "Enter correct choice!" << endl;
			break;
		}
	}
	system("pause");
}
