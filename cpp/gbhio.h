/*************************************************
 *   G BRENT HURST
 *   iogbh.h
 *   December 21, 2017 (original)
 *   August 12, 2019 (last edit)
 *
 *   I/O classes.
 *
 ************************************************/

#ifndef IOGBH_H
#define IOGBH_H

using namespace std;


/*************************************************
 *   class Delimited
 *
 *   Read and write lines/files of data
 *   whose entries are delimited by c0
 *   and whose lines are delimited by c1.
 *
 *   The esc char allows the inclusion
 *   of the delimiters in the data.
 *
 *   Uses the stl's buffered I/O.
 *
 ************************************************/

class Delimited
{
	protected:
		int ReadAnotherWord();
		void WriteAnotherChar(char c);
		void WriteLine_internal(int index);

		string filename;
		FILE* f;
		char word_delim;
		char line_delim;
		char escape_char;
		string mode;
		int error;

	public:
		//Reads a line from file f into line,
		//delimiting words with word_delim and lines with line_delim
		//and allowing entries to contain word_delim or line_delim by escape_char.
		//Returns
		//  0 if EOF or if error reading from f,
		//  1 if end of line
		int ReadLine();

		//Reads from a file f into file
		//delimiting words with word_delim and lines with line_delim
		//and allowing entries to contain word_delim or line_delim by escape_char.
		void ReadFile();

		//Public function to write "line" to file
		void WriteLine();

		//Public function to write "file" to file
		void WriteFile();

		//Print what the error is to stderr
		void PrintError();

		//Return the error code. 0 if no error. Print with PrintError().
		int Error();



		//ReadLine() stores in line, and WriteLine() writes out line
		vector<string> line;
		//ReadFile() stores in file, and WriteFile() writes out file
		vector<vector<string> > file;


		//Constructors and Destructor
		//Parameters:
		//    fn - filename
		//    m - mode ['r' or 'w']
		//    wd - word delimiter
		//    ld - line delimiter
		//    ec - escape character
		//wd, ld, and wc must be distinct
		Delimited(const string& fn, char m, char wd, char ld, char ec);
		Delimited(const string& fn, char m);
		~Delimited();
};

#endif
