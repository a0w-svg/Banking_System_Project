#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

class Logic
{
private:
	
	int accounts_number = 0; // account number
	string first_name = "";
	string last_name = "";
	float total_balance = 0.0;
	void read_data();
	void show_data();
	void write_record();
	void read_record();
	void search_record();
	void edit_record();
	void delete_record();
public:
	void Run();
};

