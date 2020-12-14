/*--------------------------
tree.h
Author: Zach H
Date: 1/6/2020
-------------------------*/
#include <string.h>
#include <iostream>
using namespace std;

class List{
  private:
    struct node
    {
       char name[128];
       node * next;
    };
    typedef node * nodeptr;
    nodeptr head;

  public:
     List()
     {
        head = NULL;
     }
     void print()
     {
       nodeptr curr = head;
       while(curr != NULL)
       {
         cout << curr->name << endl;
         curr = curr->next;
       }
     }
     void Insert(char x[])
     {
       nodeptr temp = new node;

       strcpy(temp->name, x);
       temp->next = NULL;

       if(head == NULL)
         head = temp;
       else
       {
         temp->next = head;
         head = temp;
       }
     }
     bool search(char name[])
     {
       nodeptr curr = head;
       bool answer = false;
       while(curr!=NULL)
       {
         if(strcmp(name,curr->name) == 0){
          answer = true;
        }
        curr = curr->next;
       }
       return answer;
     }
};

class tree{
  private:
    typedef struct node
    {
      int syear;
      int eyear;
      char seriesname[128];
      string seriesURL;
      List list;
      node *leftptr;
      node *rightptr;
    }*treeptr;
    treeptr rootptr;
    void InitTree()
    {
       rootptr = NULL;
    }
    void PrintBST_InOrder(treeptr treePtr);
    treeptr findpos(treeptr treePtr, char name[],int syear);
    void findyear(treeptr treePtr, int syear, int eyear);
    void findactor(treeptr treePtr,char name[]);
    int countOneNodeParents(treeptr treePtr, int count);

  public:
    tree(){
      InitTree();
    }
    void PrintTree()
    {
      PrintBST_InOrder(rootptr);
      int count = 0;
      cout << countOneNodeParents(rootptr, count) << endl;
    }
    void insert(char name[],char seriesName[],int syear)
    {
      treeptr currPtr = NULL;
      currPtr = findpos(rootptr,seriesName, syear);
      currPtr->list.Insert(name);
    }
    void lookup()
    {
      char name[128];
      cout << "enter actor name:" << endl;
      cin.getline(name,128);
      findactor(rootptr,name);
      int syear,eyear;
      cout << endl;
      cout << "enter year range: start year, end year" << endl;
      cin >> syear;
      cin >> eyear;
      cout << endl;
      findyear(rootptr,syear,eyear);
      cout << endl;
    }
    void AddNode(int syear,int eyear, char seriesname[], string seriesURL);
    bool check_duplicates(char seriesname[],int syear);
};
