/*
Map_functions.cpp
*/
#include <iostream>
#include "Queue.h"
using namespace std;
//----------Queue_Functions---------
void Queue::enQueue(int x,int y){
  nodeptr temp = new node;
  temp->x = x;
  temp->y = y;
  temp->next = NULL;
  if(head == NULL){
    head = temp;
    tail = head;
  }else{
    tail->next = temp;
    tail = temp;
  }
}
void Queue::delete_all(){
  while(head != NULL){
    nodeptr del = head;
    head = head->next;
    del->next = NULL;

    delete del;
  }
  head = NULL;
}
//-----------only allows queueing of points not in the queue----------------
void Queue::filter(int x,int y){
  if(head == NULL){
    enQueue(x, y);
  }else{
    nodeptr curr = head;
    int duplicate = 0;
    while(curr !=NULL){
      if(curr->x == x && curr->y == y){
        duplicate += 1;
        break;
      }
      curr = curr->next;
    }if(duplicate == 0){
      enQueue(x, y);
  }
}
}
//-----------Map_functions---------------------
void Map::clear(){
  for(int i = 0; i < y; ++i) {
      delete [] arr[i];
  }
  delete [] arr;
}



//-------------solve function---------------
void Queue::solve(ifstream& infile){
  Map Map_1(infile);
  int m, n;
  //---------locate S-----------------
  for(m=0;m < Map_1.y; m++){
    for(n=0;n < Map_1.x; n++){
      if(Map_1.arr[m+1][n+1] == 'S'){
        enQueue(m+1, n+1);
      }
    }
  }
  //-------solve----------
  nodeptr curr = head;
  n = curr->y;
  m = curr->x;
  while(1==1){
    if(Map_1.arr[m][n+1] != '#'){
      filter(m, n+1);
      if(Map_1.arr[m][n+1] == 'G')
        break;
    }if(Map_1.arr[m+1][n] != '#'){
      filter(m+1, n);
      if(Map_1.arr[m+1][n] == 'G')
        break;
    }if(Map_1.arr[m-1][n] != '#'){
      filter(m-1, n);
      if(Map_1.arr[m-1][n] == 'G')
        break;
    }if(Map_1.arr[m][n-1] != '#'){
      filter(m, n-1);
      if(Map_1.arr[m][n-1] == 'G')
        break;
    }if(curr->next == NULL){
      cout << endl;
        cout << "UNSOLVABLE!" << endl;
      break;
    }
  curr = curr->next;
  n = curr->y;
  m = curr->x;
}
//------------edit the existing map--------------
curr = head;
while(curr != NULL){
  m = curr->x;
  n = curr->y;
  if(Map_1.arr[m][n] != 'S' && Map_1.arr[m][n] != 'G')
    Map_1.arr[m][n] = '!';
  curr = curr->next;
}
//-----------print the map w/solution--------------------
cout << endl;
for(int i=0; i < Map_1.y;i++){
  for(int t=0; t < Map_1.x;t++){
    if(Map_1.arr[i+1][t+1] == '.'){
      cout << ' ';
    }else{
      cout << Map_1.arr[i+1][t+1];
    }
  }
  cout << endl;
}
cout << "\n ! mark the path! YAY!!!" << endl;
Map_1.clear();
delete_all();
}
