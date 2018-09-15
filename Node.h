//Course: SENG1120
//Coded by: Tom Williams
//Student Number: 3282012
#ifndef NODE_H
#define NODE_H
#include "Student.h"

struct Node
{
public:
  // Constructor
  Node();
  Node(Student newStudent);

  // Destructor
  ~Node();

  // Getters
  Node *getNext();
  Node *getPrev();
  Student *getStudent();

  // Setters
  void setNext(Node *newNext);
  void setPrev(Node *newPrev);
  void setStudent(Student *newStu);

  //Misc
friend std::ostream& operator<<(std::ostream& os, Node& dn);

private:
Student *student;
Node *next;
Node *prev;
};

#endif
