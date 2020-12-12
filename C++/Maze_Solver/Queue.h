/*-------------------------
 Queue.h
 Author: Zach H
 Date: 11/14/2019
-------------------------*/

#include<fstream>
#include<iostream>
using namespace std;

class Queue{
  private:
    struct node  // struct for the node
    {
       int x, y;
       node * next;
    };
    typedef node * nodeptr;
    nodeptr head;
    nodeptr tail;

  public:
     Queue() // constructor
     {
        head = NULL;
        tail = head;
     }
     // prototypes
     void enQueue(int x,int y);
     void delete_all();
     void solve(ifstream& infile);
     void filter(int x,int y);
};
// used to create the maps an object so it can be accessed
// from any function
class Map{
public:
  char **arr;
  int x;
  int y;
  Map(ifstream& infile){
    x = 0;
    y = 0;
    infile >> x >> y;
    //create array
    arr = new char*[y+2];
    for(int i=0;i < y+2;++i){
      arr[i] = new char[x+2];
    }
    //fill with # for border
    for(int m=0;m < y+2; m++){
      for(int n=0;n < x+2; n++){
        arr[m][n] = '#';
      }
    }
    //translate map into array
    for(int m=0;m < y; m++){
      for(int n=0;n < x; n++){
        char d;
        infile >> d;
        arr[m+1][n+1] = d;
      }
    }
  }
void clear();//deletes the array
};




