//Course: SENG1120
//Coded by: Tom Williams
//Student Number: 3282012
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>
#include <iostream>
#include "Node.h"

class LinkedList
{
public:
  // Constructors
  LinkedList();

  // Destructor
    ~LinkedList();

  // Getters
  Node* getHead();
  Node* getTail();
  int getCount();

  // Adders
  void addFirst(Node*);
  void addToHead(Student);
  void addToTail(Student);
  void concatenate(LinkedList second);

  // Removers
  void deleteNode(Node*);
  void remove(std::string Name);
  void empty();

  // Sorters
  Node* findName(std::string Name);
  bool sorted();
  void order();

  // Misc.
  double sumList(Node* curr);
  double calcAverage();
  int count(std::string name);

  // Overloaders
  void operator+=(LinkedList& rhs);
  friend std::ostream& operator<<(std::ostream& os, LinkedList& dl);


private:
  // Member Variables
  Node *head;
  Node *tail;
  int ncount;
};

#endif
