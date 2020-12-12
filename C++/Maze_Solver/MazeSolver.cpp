/*-------------------------
 Maze Sloving program
 Author: Zach H
 Date: 11/14/2019

 Takes in a text file with a map or
 multiple maps in it, then it shows
 all possible paths including the
 path to the goal. if the Maze is
 not solvable the program will
 identify it

 Map Format:
 the first line is the dimensions (width, height)
 the next lines are for the mae using the following
 symbols:
 S = start
 G = goal
 # = wall
 . = path

 Example:
 4 4
 S..#
 .#..
 .##.
 ...G
-------------------------*/
#include<iostream>
#include<fstream>
#include<string.h>
#include "Queue.h"
using namespace std;

int main(){
  string file;
  Queue Queue_1;
  char answer = 'y', file_answer;
  cout << "which file?" << endl;
  cin >> file;
  ifstream infile;
  infile.open(file);
  while(answer == 'y'){
    //-----------------searching--------------
    Queue_1.solve(infile);
    //------prompt-----------
    cout << endl;
    cout << "would you like to do the next one? (y or n)" << endl;
    cin >> answer;
    cout << "would you like to do another file? (y or n)" << endl;
    cin >> file_answer;
    if(file_answer == 'y'){
      infile.close();
      cout << "which file?" << endl;
      cin >> file;
      infile.open(file);
    }
  }
}


