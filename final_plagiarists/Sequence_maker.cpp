#include "Sequence_maker.h"

/*
	TYPE				:  CONSTRUCTOR
	FUNCTION NAME	:  Sequence_maker
	INPUT		  		:  string(line from a file),int(number of words per sequence)
	OUTPUT 			:  NONE
	DESCRIPTION		:  assigns values to internal variables
*/

Sequence_maker :: Sequence_maker(string s_line,int n)
{
	line_tb_split = s_line;
	words_to_be_printed = n;
	words_in_line = give_words_in_line();
};

/*
	FUNCTION NAME	:  give_words_in_line
	INPUT		  		:  NONE
	OUTPUT 			:  int
	DESCRIPTION		:  number of words in a particular line 
							it will also checks if there are also two spaces or more...
*/

int Sequence_maker :: give_words_in_line()
{
	int value = 0;
	for (int i = 0 ; i < line_tb_split.length(); i++) 
	{
		if (line_tb_split[i] == ' ') 
		{
			if (line_tb_split[i+1] != ' ') 
				value++;
		}
	}
	value++;
	return value;
}

/*
	FUNCTION NAME	:  extract_ith_word
	INPUT		  		:  int
	OUTPUT 			:  string
	DESCRIPTION		:  returns ith word from a line which is initilized in constructor
*/

string Sequence_maker :: extract_ith_wrd(int index)
{
	int count = 0;
	string word;
	for (int i = 0 ; i < line_tb_split.length(); i++)
	{
		if (line_tb_split[i] == ' ') 
		{
			if (line_tb_split[i+1] != ' ') 
			{
				count++;
				if (count == index)
					return word;
				word ="";
			}
		}
		else 
			word += line_tb_split[i];
	}
}

/*
	FUNCTION NAME	:  print_to_file
	INPUT		  		:  string(output file name to be printed in file)
	OUTPUT 			:  NONE
	DESCRIPTION		:  print n word sequences into output file
*/

void Sequence_maker :: print_to_file(string outp)
{
	int j = 0;
	string s;
	ofstream output_file (outp.c_str(),ios::app | ios::out);
	if(words_in_line <= words_to_be_printed)
		output_file << line_tb_split << '\n';
	else if(output_file.is_open())
	{
		for(int i = 0;i<=words_in_line - words_to_be_printed; i++)
		{
			j = 0;
			while(j != words_to_be_printed)
			{
				s = extract_ith_wrd(i+j+1);
				output_file << s << " ";
				j++;
			}
			output_file << '\n';
		}
	}
	else
		cout<<"Output file is not opened"<<endl;
	output_file.close();
}

/*
	TYPE				:  DESTRUCTOR
	FUNCTION NAME	:  ~Sequence_maker
	INPUT		  		:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  Nothing
*/

Sequence_maker :: ~Sequence_maker()
{
}
