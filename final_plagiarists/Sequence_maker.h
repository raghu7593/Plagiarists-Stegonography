#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Sequence_maker
{
	public:

		int words_in_line;
		int words_to_be_printed;
		string line_tb_split;
		
		Sequence_maker(string s2,int n);
		int give_words_in_line();
		string extract_ith_wrd(int i);
		void print_to_file(string outp);
		~Sequence_maker();
};
