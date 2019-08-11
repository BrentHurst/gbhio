/*************************************************
 *   G BRENT HURST
 *   iogbh.h
 *   December 21, 2017 (original)
 *   December 27, 2017 (last edit)
 *
 *   Functions that perform specific io tasks.
 *
 ************************************************/

#ifndef IOGBH_H
#define IOGBH_H

//#include <cstdlib>
//#include <string>
//#include <vector>

using namespace std;


/*************************************************
 *   Read and write lines/files of data
 *   whose entries are delimited by c0
 *   and whose lines are delimited by c1.
 *
 *   The esc char allows the inclusion
 *   of the delimiters in the data.
 *
 *   If no row delimiter, pass -1 to c1.
 *   If no esc, pass -1 to esc.
 *
 *   FILE* f must be open. No error checks
 *   are performed.
 *   The vector isn't required to be empty
 *   when using GetLine or GetFile, but
 *   contents will be overwritten.
 *
 *   Uses the stl's buffered io.
 *
 *   Return Values
 *     int GetLine()
 *       0 if EOF or if error reading from f
 *       1 if end of line
 *
 *   Definitions in iogbhDelimitedLineFile.cpp
 *
 ************************************************/

int GetDelimitedLine(FILE* f,char c0,int c1,int esc,vector<string>& rv);
void GetDelimitedFile(FILE* f,char c0,int c1,int esc,vector<vector<string> >& rv);
void PutDelimitedLine(FILE* f,char c0,int c1,int esc,vector<string>& v);
void PutDelimitedFile(FILE* f,char c0,int c1,int esc,vector<vector<string> >& v);

#endif
