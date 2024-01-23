/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
// checking if the list is empty and if so, nothing to split
if (in == nullptr) {
  odds = nullptr;
  evens = nullptr;
  return;
}

// separate node
Node* curr = in;
in = in->next;

// recursively split
split(in, odds, evens);

// if the input value is odd
if (curr->value % 2 == 1) {
  // add the current node to the odds list
  curr->next = odds;
  odds = curr;
  // even case 
} else {
  // add the current node to the evens list 
  curr->next = evens;
  evens = curr;
  }
}
