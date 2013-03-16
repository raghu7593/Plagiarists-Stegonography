#include"hashtable_creator.h"
#include"primes.h"

/*
	TYPE				:	CONSTRUCTOR with arguments
	FUNCTION NAME	:  Hashtable_creator
	INPUT		  		:  string
	OUTPUT 			:  NONE
	DESCRIPTION		:  Assigns values to local variables
*/

Hashtable_creator :: Hashtable_creator(string & name)
{
	file_name = name;
	table_size = sz_store(no_sequences_in_file());
	
	table_entry entry;
	hash_table.assign(table_size,entry);
	
	readfile_fill();
}

/*
	TYPE				:	CONSTRUCTOR without arguments
	FUNCTION NAME	:  Hashtable_creator
	INPUT		  		:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  Nothing
*/

Hashtable_creator :: Hashtable_creator()
{}

/*
	FUNCTION NAME	:  hash_fun
	INPUT		  		:  string
	OUTPUT 			:  int
	DESCRIPTION		:  converts string into integer by using polynomial...
*/

long int Hashtable_creator :: hash_fun(string &s)
{
	int k1,k2=0;
	long int code;
	k1 = s.length();
	code = 0;
	while(s[k2] != '\0')
	{
		code += (s[k2] * (pow(3,k1-k2-1)));
		code %= table_size;
		while(code < 0)
		code += table_size;
		k2++;
	}
	code %= table_size;
	while(code < 0)
		code += table_size;
	return code;
}

/*
	FUNCTION NAME	:  operator=
	INPUT		  		:  Hashtable_creator
	OUTPUT 			:  NONE
	DESCRIPTION		:  Just like copy constructor(operator overloading)
*/

void Hashtable_creator:: operator= (Hashtable_creator& rhs)
{
	file_name = rhs.file_name;
	table_size = rhs.table_size;
	
	hash_table = rhs.hash_table;
}

/*
	FUNCTION NAME	:  no_sequences_in_file
	INPUT		  		:  NONE
	OUTPUT 			:  int
	DESCRIPTION		:  counts number of sequences in the file
*/
	
long int Hashtable_creator :: no_sequences_in_file()
{
    long int no_of_sequences = 0;
	string line;

	file.open(file_name.c_str());
	while(!file.eof())
	{
		getline(file, line);
		no_of_sequences ++;
	}
	file.close();
	
	return no_of_sequences;
}	

/*
	FUNCTION NAME	:  sz_store
	INPUT		  		:  int
	OUTPUT 			:  int
	DESCRIPTION		:  gives a prime number of more than double size og the input integer
							for this we have created primes.h which contains an array of prime numbers
*/

long int Hashtable_creator :: sz_store(long int min_size)
{
	min_size = min_size *2;
	int sz = 41538,lower_bound,upper_bound,middle;
	lower_bound = 0;
	upper_bound = 41537;
	while (1)
	{
		middle = (lower_bound + upper_bound)/2;
		if((lower_bound == upper_bound - 1) or (lower_bound == upper_bound))
			return prime[upper_bound];
		else if(prime[middle] > min_size)
			upper_bound = middle;
		else if(prime[middle] < min_size)
			lower_bound = middle;
	}
}
	
/*
	FUNCTION NAME	:  insert
	INPUT		  		:  string
	OUTPUT 			:  NONE
	DESCRIPTION		:  inserts string into hash table first it checks for its position and inserts into it.
*/

void Hashtable_creator :: insert(string & s)
{
	long int curr_pos = findpos(s);
	table_entry entry; 
	if(hash_table[ curr_pos ].status == empty) 
	{
		entry.status = full; entry.sequence = s;
		hash_table[ curr_pos ] = entry;
	} 	
}

/*
	FUNCTION NAME	:  findpos
	INPUT		  		:  string
	OUTPUT 			:  int
	DESCRIPTION		:  gives particular position such that string can be inserted first it takes int from hash_fun and afterwards quadratic probing
*/
	
long int Hashtable_creator :: findpos(string & s)
{
	long int curr_index = hash_fun(s) % table_size;
	
	long int i=1;
	while( hash_table[ curr_index ].status != empty and hash_table[ curr_index ].sequence != s)
			{
				curr_index = curr_index + 2*(i++) - 1;
				if(curr_index >= table_size)
					curr_index -= table_size;
			}  
	return curr_index;
}

/*
	FUNCTION NAME	:  readfile_fill
	INPUT		  		:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  inserts each and every string from file into the hashtable
*/

void Hashtable_creator :: readfile_fill()
{
	file.open(file_name.c_str());
	string line;
	while(!file.eof())
	{
		getline(file,line);
		insert(line);	
	}
	file.close();
}
