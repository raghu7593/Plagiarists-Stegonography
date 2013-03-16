#include"find_file2_in_table1.h"

/*
	TYPE				:	CONSTRUCTOR
	FUNCTION NAME	:  Find_file2_in_table1
	INPUT		  		:  Hashtable_creator,Hashtable_creator,string(when referance txt document is present)
	OUTPUT 			:  NONE
	DESCRIPTION		:  assigns values to its local variables
*/

Find_file2_in_table1 :: Find_file2_in_table1 (Hashtable_creator  & table_creator,Hashtable_creator  & reftable_creator, string name)
{
	table_creator1 = table_creator;
	ref_table_creator = reftable_creator;
	filename2 = name;
	no_matches = 0;
	no_not_matches = 0;
	no_matches_ref = 0;
	search_for_2in1_with_ref();	
}

/*
	TYPE				:	CONSTRUCTOR
	FUNCTION NAME	:  Find_file2_in_table1
	INPUT		  		:  Hashtable_creator,string(when referance txt document was not there)
	OUTPUT 			:  NONE
	DESCRIPTION		:  assigns values to its local variables
*/

Find_file2_in_table1 :: Find_file2_in_table1 (Hashtable_creator  & table_creator, string name)
{
	table_creator1 = table_creator;
	filename2 = name;
	no_matches = 0;
	no_not_matches = 0;
	search_for_2in1();	
}

/*
	FUNCTION NAME	:  search_for_2in1_with_ref
	INPUT		  		:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  if matches are present junt increments the variable by checking in referance txt document.
*/

void Find_file2_in_table1 :: search_for_2in1_with_ref()
{
	file2.open(filename2.c_str());
	
	string line;
	while(!file2.eof())
	{
		getline(file2,line);
		
		if(isMatch(line,ref_table_creator)) {no_matches_ref++;}
		else		
		{	
			if(isMatch(line,table_creator1)) no_matches++;
			else no_not_matches++;
		}
	}

	file2.close();
}

/*
	FUNCTION NAME	: 	search_for_2in1
	INPUT		  		:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  if matches are present junt increments the variable.
*/

void Find_file2_in_table1 :: search_for_2in1()
{
	file2.open(filename2.c_str());
	
	string line;
	while(!file2.eof())
	{
		getline(file2,line);
		
		if(isMatch(line,table_creator1)) no_matches++;
		else no_not_matches++;
	}

	file2.close();
}

/*
	FUNCTION NAME	:  isMatch
	INPUT		  		:  Hashtable_creator,string
	OUTPUT 			:  true/false
	DESCRIPTION		:  checks weather string is in hash table or not returns true if string is present in hash table else false
*/

bool Find_file2_in_table1 :: isMatch(string line, Hashtable_creator & table_creator)
{
	long int prob_pos = table_creator.findpos(line);
	
	if (table_creator.hash_table [ prob_pos ].status == empty) return false;
	else if (table_creator.hash_table [ prob_pos ].sequence == line) return true;
}

