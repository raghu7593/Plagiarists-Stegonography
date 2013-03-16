#include<iostream>
#include <fstream>
#include "find_file2_in_table1.cpp"
#include "sequencefiles_creator.cpp"
using namespace std;

int no_of_sequences(string&);
string give_app_name(string&);

/*
	results of how much percent copying is done by any two files is shown in file test_results.ods
	if there is a referance file (just like common file given to all) then total number of sequences copied is number of sequences 
		copied a from b that are not in referance file.
	if no referance file then simply number of sequences matched.
	if it is yes or no object of Sequencefiles_creator class will be created and create_output function is called.
	it will creates output files of given sequence size. 
	created output files are send into hash table ane number of matched sequences will be counted
*/

int main()
{
	string s;
	char c = 32;
	ofstream result;
	result.open("test_results.ods"); //opening test_results.ods where the output results will be printed
	
	ifstream nofw("choice.txt");
	string choice;
	getline(nofw,choice);
	
	std::string mystring = choice;
	nofw.close();

	Sequencefiles_creator list_creator;
	list_creator.create_output();  //calling create_output function
	
	int no_files_tb_tested = list_creator.no_of_files();  //total number of files given
	int output_array[no_files_tb_tested][no_files_tb_tested];  //output results array
	
	string inpfile_names_array[no_files_tb_tested];   //file names array
	 string filename;
	 ifstream inpfile("list_of_filenames.txt");  
	 
	for(int i=0; i<no_files_tb_tested; i++)
	{
		getline(inpfile,filename);
		inpfile_names_array[i] = give_app_name(filename);
	}
	
	if (mystring == "yes")		//checks condition yes or no
	{
		int no_of_sequences_array[no_files_tb_tested];
		
		
		s = list_creator.output_name(1);
		Hashtable_creator ref_table(s);		//Hashtable_creator objects are created here
		
		int curr_matches;
		int curr_matches_ref;
		
		for(int i=2; i <= no_files_tb_tested; i++)
		{
			s = list_creator.output_name(i);
			
			no_of_sequences_array[i-1] = no_of_sequences(s);
			
			Hashtable_creator curr_table(s);
			
			for(int j=2; j <= no_files_tb_tested; j++)
			{
				s = list_creator.output_name(j);
				Find_file2_in_table1 curr_finding_with_ref(curr_table,ref_table,s);  
				
				curr_matches = curr_finding_with_ref.no_matches;			//number of matches between two output files
				curr_matches_ref = curr_finding_with_ref.no_matches_ref; 
				
				output_array[i-1][j-1] = curr_matches;
				}
			
		 }	
		 
		 //priting output in test_results
		 
		 result<<c;
		 for(int i=1; i < no_files_tb_tested; i++)	
		 		result<<inpfile_names_array[i]<<c;
		 result<<"\n";
		 	
		 for(int i=1; i < no_files_tb_tested; i++)
			 {	 	
		 	result<<inpfile_names_array[i]<<c;
		 	for(int j=1; j < no_files_tb_tested; j++)
		 		result<<output_array[i][j]<<"("<<(((float)output_array[i][j]*100)/(float)no_of_sequences_array[j])<<")"<<c;
		 	result<<"\n";
		 }
		 	  
	}
	
	//for no case also same will be done with extra checking of referance file as described above
	
	else 
	{
		
		for(int i=1; i <= no_files_tb_tested; i++)
		{
			s = list_creator.output_name(i);
			Hashtable_creator curr_table(s);
			int curr_matches;
			
			for(int j=1; j <= no_files_tb_tested; j++)
			{
				s = list_creator.output_name(j);
				Find_file2_in_table1 curr_finding(curr_table, s);
				
				curr_matches = curr_finding.no_matches;
				
				output_array[i-1][j-1] = curr_matches;
			}
			
		 }	
		 
		 result<<c; 
		 for(int i=0; i < no_files_tb_tested; i++)
		 	result<< inpfile_names_array[i]<<c;
		 result<<"\n";
		 	
		 for(int i=0; i < no_files_tb_tested; i++)
		 {	 	
		 	result<< inpfile_names_array[i]<<c;
		 	for(int j=0; j < no_files_tb_tested; j++)
		 		result<<output_array[i][j]<<"("<<(((float)output_array[i][j]*100)/(float)output_array[j][j])<<")"<<c;
		 	result<<"\n";
		 }
	
	}
	return 0;
}

/*
	FUNCTION NAME	:  no_of_sequences
	INPUT		  		:  string
	OUTPUT 			:  int
	DESCRIPTION		:  number of lines in file.
*/


int no_of_sequences(string& file_name)
{
	ifstream file(file_name.c_str());
	
	string line;
	int number=0;
	
	while(!file.eof())
	{
		getline(file,line);
		number++;
	}
	
	return number;
}

/*
	FUNCTION NAME	:  give_app_name
	INPUT		  		:  string
	OUTPUT 			:  string
	DESCRIPTION		:  returns appropriate file name by removine all the path
							Example: input - /usr/raghu/Desktop/abc.txt, output - abc.txt
*/

string give_app_name(string& file_path)
{
	int len = file_path.length();
	while(file_path[--len] != '/'){}
	string file_name = file_path.substr(++len);
	return file_name;
}
