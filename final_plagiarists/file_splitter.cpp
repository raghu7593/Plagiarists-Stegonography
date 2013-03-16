#include"file_splitter.h"
#include <string>

/*
	TYPE				:  CONSTRUCTOR
	FUNCTION NAME	:  File_splitter
	INPUT		  		:  string(input file name),string(output file name),int(number of words per sequence)
	OUTPUT 			:  NONE
	DESCRIPTION		:  assigns values to internal variables
*/


File_splitter::File_splitter(string inp, string outp, int wps)
{
	input = inp;
	output = outp;
	words_per_sequence = wps;
}

/*
	FUNCTION NAME	:  splitter_fun
	INPUT		  		:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  creates an object of Sequence_maker and calls print_to_file function sends each line in input file and 
							words per sequence to this object.
*/

void File_splitter::splitter_fun()
{
	input_file.open(input.c_str());
	output_file.open(output.c_str());
	
	string line_to_be_split;
	
	while(!input_file.eof())
	{
		getline(input_file,line_to_be_split);
		Sequence_maker sequence_maker(line_to_be_split,words_per_sequence);
		sequence_maker.print_to_file(output);
	}
	input_file.close();
	output_file.close();
}
