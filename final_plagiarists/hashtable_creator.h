#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<math.h>
using namespace std;

enum Status {empty,full};

class Hashtable_creator
{
public:
	string file_name;
	ifstream file;
	long int table_size;
	
	//structure for a particular position in hash table is empty or full i.e,status and string in that position
	
	struct table_entry
	{
		Status status; 
		string sequence;
		
		table_entry(Status st = empty, const string & s = " ")
		: status(st) , sequence(s){}
	};
	
	vector<table_entry> hash_table;
	
	//functions of Hashtable_creator class
		
	Hashtable_creator(string & name);
	Hashtable_creator();
	void operator= (Hashtable_creator& rhs);
	long int no_sequences_in_file();
	long int sz_store(long int min_size);
	void insert(string & s);
	long int hash_fun(string &s);
	long int findpos(string & s);
	void readfile_fill();
};
