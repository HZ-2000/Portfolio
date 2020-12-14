/*--------------------------
tree.cpp
Author: Zach H
Date: 1/6/2020
-------------------------*/
#include<fstream>
#include<iostream>
#include "tree.h"
using namespace std;

void get_series_name(char line[], char seriesname[]);
void GetYears( char line[], int & yStart, int & yEnd );
void GetSubString( char s[], int start, int end, char res[] );
int IndexOf( char s[], char c );
void RemoveBlanksFromString( char s[] );

int main()
{
  tree tree_1;

  ifstream infile("tv.txt",ios::in);

  //variables for each part of data
  const int MAX_LINE = 128;
  char line[MAX_LINE];
  char seriesName[MAX_LINE];
  char seriesCategory[MAX_LINE];
  char seriesURL[MAX_LINE];
  char actor[MAX_LINE];

  int yStart, yEnd;

  // main loop for reading file
  while(infile.getline(line, MAX_LINE))
  {
    get_series_name( line, seriesName );
    GetYears( line, yStart, yEnd );
    infile.getline( seriesCategory, MAX_LINE/2 );
    infile.getline( seriesURL, MAX_LINE );
    if(tree_1.check_duplicates(seriesName,yStart) == false)
    {
      tree_1.AddNode(yStart, yEnd, seriesName, seriesURL);

      infile.getline(line, MAX_LINE/2);
      while(strlen(line) > 0)
      {
        tree_1.insert(line,seriesName,yStart);
        infile.getline(line, MAX_LINE/2);
      }
    }
  }
  tree_1.PrintTree();
  cout << endl;
  //tree_1.lookup();
  infile.close();
}

void get_series_name(char line[], char seriesname[])
{
  int yearStart;
  yearStart = IndexOf( line, '(' );
  GetSubString( line, 0, yearStart-1, seriesname );
}

void GetYears( char line[], int & yStart, int & yEnd )
{
  char tmpString[8];
  char yearString[16];
  int yearStart, yearEnd;

  yearStart = IndexOf( line, '(' );
  yearEnd = IndexOf( line, ')' );
  GetSubString( line, yearStart+1, yearEnd-yearStart-1, yearString );
  GetSubString( yearString, 0, 4, tmpString );
  yStart = atoi( tmpString );
  GetSubString( yearString, 4, 7, tmpString );
  yEnd = atoi( tmpString );
  yEnd *= -1;
}

void GetSubString( char s[], int start, int end, char res[] )
{
  int i;
  int iRes = 0;

  for( i = start ; i < start+end ; i++ )
  {
    res[iRes++] = s[i];
  }
  res[iRes] = '\0';
  RemoveBlanksFromString( res );
}

void RemoveBlanksFromString( char s[] )
{
  int sLen = strlen( s );
  for( int i = sLen ; i >= 0 ; i-- )
  {
    if( isalpha(s[i]) )
      break;
    if( s[i] == ' ' )
      s[i] = '\0';
  }
}

int IndexOf( char s[], char c )
{
  int i = 0;
  while( s[i] != '\0' && s[i] != c )
    i++;
  return i;
}
