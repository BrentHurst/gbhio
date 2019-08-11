/*************************************************
 *   G BRENT HURST
 *   Delimited.cpp
 *   December 21, 2017 (original)
 *   August 11, 2019 (last edit)
 *
 *   #include "iogbh.h"
 *
 ************************************************/


#include <cstdio>
#include <vector>
#include <string>
#include "gbhio.h"

using namespace std;

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
		int ReadLine();
		void ReadFile();
		void WriteLine();
		void WriteFile();
		void PrintError();
		int Error();

		vector<string> line;
		vector<vector<string> > file;

		Delimited(const string& fn, char m, char wd, char ld, char ec);
		Delimited(const string& fn, char m);
		~Delimited();
};


Delimited::Delimited(const string& fn, char m, char wd, char ld, char ec)
{
	error = 0;

	filename = fn;
	word_delim = wd;
	line_delim = ld;
	escape_char = ec;

	if(escape_char == word_delim || escape_char == line_delim || line_delim == word_delim)
		error |= (1 << 0);

	if(m == 'r')
		mode = "r";
	else if(m == 'w')
		mode = "w";
	else
		error |= (1 << 1);

	if(!(f = fopen(filename.c_str(),mode.c_str())))
		error |= (1 << 2);
}

Delimited::Delimited(const string& fn, char m)
{
	error = 0;

	filename = fn;
	word_delim = ',';
	line_delim = '\n';
	escape_char = '\\';

	if(m == 'r')
		mode = "r";
	else if(m == 'w')
		mode = "w";
	else
		error |= (1 << 1);

	if(!(f = fopen(filename.c_str(),mode.c_str())))
		error |= (1 << 2);
}
Delimited::~Delimited()
{
	fclose(f);
}

void Delimited::PrintError()
{
	if(error & (1 << 0))
		fprintf(stderr,"Error 0: Word_delim, line_delim, and escape_char must all be distinct.\n");
	if(error & (1 << 1))
		fprintf(stderr,"Error 1: Mode must be either 'r' or 'w'.\n");
	if(error & (1 << 2))
		fprintf(stderr,"Error 2: Could not open file \"%s\".\n",filename.c_str());
}

int Delimited::Error()
{
	return error;
}




//Reads a word from a file f into vector<string> line,
//delimiting words with word_delim and lines with line_delim
//and allowing entries to contain word_delim or line_delim by escape_char.
//Returns
//  -1 if end of word
//  0 if EOF or if error reading from f,
//  1 if end of line
int Delimited::ReadAnotherWord()
{
	char c;
	int i;
	bool escape;

	escape=0;
	line.resize(line.size() + 1);
	while((i = fread(&c, sizeof(char), 1, f)))
	{
		if(escape)
		{
			line.back().push_back(c);
			escape=false;
		}
		else if(c == word_delim)
			return -1;
		else if(c == line_delim)
			return 1;
		else if(c == escape_char)
			escape = true;
		else
			line.back().push_back(c);
	}
	return 0;
}


//Reads a line from file f into line,
//delimiting words with word_delim and lines with line_delim
//and allowing entries to contain word_delim or line_delim by escape_char.
//Returns
//  0 if EOF or if error reading from f,
//  1 if end of line
int Delimited::ReadLine()
{
	int i;

	line.clear();

	while((i = ReadAnotherWord()) == -1);

	return i;
}

//Reads from a file f into file
//delimiting words with word_delim and lines with line_delim
//and allowing entries to contain word_delim or line_delim by escape_char.
void Delimited::ReadFile()
{
	file.clear();

	//read while not EOF and no error
	while(ReadLine())
		file.push_back(line);

	//If the last line contains no data, delete it
	if(file.back().size() == 1 && file.back().at(0).empty())
		file.pop_back();

	line.clear();
}

//Writes a char c out to a file f,
//escaping if necessary
void Delimited::WriteAnotherChar(char c)
{
	//escape if about to write c0 or c1 or esc
	if(c == word_delim || c == line_delim || c == escape_char)
		fwrite(&escape_char,sizeof(char),1,f);
	fwrite(&c,sizeof(char),1,f);
}

void Delimited::WriteLine_internal(int index)
{
	unsigned int i,j;

	vector<string>* v;

	v = (index == -1) ? &line : &(file[index]);

	for(i=0; i<v->size(); i++)
	{
		//write out char by char
		for(j=0; j<v[i].size(); j++)
			WriteAnotherChar(v->at(i).at(j));

		//put the word delimiter after all but the last
		if(i<v->size()-1)
			fwrite(&word_delim,sizeof(char),1,f);
	}

	//at the end of the line, put the line delimiter
	fwrite(&line_delim,sizeof(char),1,f);
}

void Delimited::WriteLine()
{
	WriteLine_internal(-1);
}

void Delimited::WriteFile()
{
	int i;

	for(i=0; i<(int)file.size(); i++)
		WriteLine_internal(i);
}
