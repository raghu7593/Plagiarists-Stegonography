#include "file_splitter.cpp"
#include "sequencefiles_creator.h"
#include <cstdlib>
#include <string>
#include <sstream>

/*
	FUNCTION NAME	:  output_name
	INPUT		  		:  int
	OUTPUT 			:  string
	DESCRIPTION		:  sample input - 15,corresponding output - output15
*/

string Sequencefiles_creator :: output_name(int i)
{
	string s = "output";
	
	std::string st;
	std::stringstream out;
	out << i;
	st = out.str();

	s = s + st;
	return s;
}

/*
	FUNCTION NAME	:  create_output
	INPUT		  		:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  creates object for File_splitter for each and every line in lise_of_filenames.txt and calls splitter function
*/


void Sequencefiles_creator :: create_output()
{
	ifstream a("list_of_filenames.txt");
	ifstream b("no_of_words.txt");
	string line;
	int i = 1;
	getline(b, line);
	b.close();
	std::string myString = line;
	int value = atoi(myString.c_str());
	if(!a.is_open()) cout<<"Error in opening the file"<<endl;
	while(!a.eof())
	{
		getline(a, line);
		if(line == "") break;
		File_splitter file_splitter(line,output_name(i),value);
		file_splitter.splitter_fun();
		i++;
	}
	a.close();
}

/*
	FUNCTION NAME	:  no_of_files
	INPUT		  		:  NONE
	OUTPUT 			:  int
	DESCRIPTION		:  number of lines in that file
*/


int Sequencefiles_creator :: no_of_files()
{
	ifstream a("list_of_filenames.txt");
	string line;
	int i = 1;
	while(!a.eof())
	{
		getline(a, line);
		if(line == "") break;
		i++;
	}
	a.close();
	i--;
	return i;
}
