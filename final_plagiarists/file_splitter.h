#include<iostream>
#include<fstream>

#include"Sequence_maker.cpp"


class File_splitter 
{	
public:
	ifstream input_file;
	ofstream output_file;
	
	string input;
	string output;
	
	int words_per_sequence;
	
	File_splitter(string inp, string outp, int wps);
	
	void splitter_fun();	

};
