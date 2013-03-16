#include"hashtable_creator.cpp"

//	main usage of this class is for number of strings matched from a file and from hashtable

class Find_file2_in_table1
{
public:
	Hashtable_creator table_creator1;
	Hashtable_creator ref_table_creator;
	string filename2;
	ifstream file2;
	
	int no_matches;
	int no_not_matches;
	
	int no_matches_ref;
	
	//functions for this class
	
	Find_file2_in_table1(Hashtable_creator  & table_creator,Hashtable_creator  & reftable_creator, string name);
	Find_file2_in_table1 (Hashtable_creator  & table_creator, string name);
	
	void search_for_2in1_with_ref();
	void search_for_2in1();
	
	bool isMatch(string line, Hashtable_creator & table_creator);
};
