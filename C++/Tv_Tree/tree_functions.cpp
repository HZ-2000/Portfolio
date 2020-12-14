/*--------------------------
tree_functions.cpp
Author: Zach H
Date: 1/6/2020
-------------------------*/
#include<iostream>
#include "tree.h"
#include<string.h>
using namespace std;

void tree::AddNode(int syear,int eyear,char seriesname[], string seriesURL)
{
   treeptr newPtr;

   newPtr = new node;

   newPtr->syear = syear;
   newPtr->eyear = eyear;
   strcpy(newPtr->seriesname,seriesname);
   newPtr->seriesURL = seriesURL;
   newPtr->leftptr = NULL;
   newPtr->rightptr = NULL;

   if( rootptr == NULL )
   {
      rootptr = newPtr;
   }
   else
   {
      treeptr treePtr = rootptr;
      treeptr targetNodePtr;

      while( treePtr != NULL )
      {
        targetNodePtr = treePtr;
        if( syear == treePtr->syear )
           treePtr = treePtr->rightptr;
        else if( syear < treePtr->syear )
           treePtr = treePtr->leftptr;
        else
           treePtr = treePtr->rightptr;
      }

      if( syear < targetNodePtr->syear )
         targetNodePtr->leftptr = newPtr;
      else
         targetNodePtr->rightptr = newPtr;
    }
}

void tree::PrintBST_InOrder(treeptr treePtr)
{
   if( treePtr != NULL)
   {
     PrintBST_InOrder( treePtr->leftptr );

     cout << treePtr->seriesname << endl;
     cout << endl;

     PrintBST_InOrder( treePtr->rightptr );
   }
}

tree::treeptr tree::findpos(treeptr treePtr, char name[], int syear)
{
   if(treePtr != NULL)
   {
    if(strcmp(name,treePtr->seriesname) == 0)
        return  treePtr;
    else if(syear < treePtr->syear)
       return findpos(treePtr->leftptr, name,syear);
    else
       return findpos(treePtr->rightptr, name,syear);
   }
   else
   {
     return NULL;
   }
}

void tree::findyear(treeptr treePtr, int syear, int eyear)
{
  if( treePtr != NULL)
  {
    findyear(treePtr->leftptr,syear,eyear);

    if(treePtr->syear >= syear && treePtr->eyear <= eyear)
      cout << treePtr->seriesname << endl;

    findyear(treePtr->rightptr,syear,eyear);
  }
}

void tree::findactor(treeptr treePtr,char name[])
{
  if( treePtr != NULL)
  {
    findactor(treePtr->leftptr,name);

    if(treePtr->list.search(name) == true)
      cout << treePtr->seriesname << endl;

    findactor(treePtr->rightptr,name);
  }
}

bool tree::check_duplicates(char seriesname[],int syear){
  treeptr currPtr = NULL;
  currPtr = findpos(rootptr,seriesname, syear);

  if(currPtr != NULL)
    return true;
  else
    return false;
}

int tree::countOneNodeParents(treeptr treePtr, int count){
  if(treePtr != NULL)
  {
    countOneNodeParents(treePtr->leftptr, count);

    if(treePtr->rightptr == NULL  && treePtr->leftptr != NULL)
      count += 1;
    else if(treePtr->rightptr != NULL  && treePtr->leftptr == NULL)
      count +=1;

    countOneNodeParents(treePtr->rightptr, count);
  }
  return count;
}
