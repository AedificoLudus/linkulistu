//Course: SENG1120
//Coded by: Tom Williams
//Student Number: 3282012
#include "Node.h"
Node::Node()
{
  next = nullptr;
  prev = nullptr;
  nStudent = nullptr;
}

Node::Node(Student newStudent)
{
  next = nullptr;
  prev = nullptr;
  nStudent = &newStudent;
}


// Empty Destructor
Node::~Node(){
   free(this);
}


// Getters
Node* Node::getNext()
{
  return next;
}

Node* Node::getPrev()
{
  return prev;
}

Student* Node::getStudent()
{
  return nStudent;
}


// Setters
void Node::setNext(Node *newNext)
{
  next = newNext;
}

void Node::setPrev(Node *newPrev)
{
  prev = newPrev;
}

void Node::setStudent(Student *newStu)
{
  nStudent = newStu;
}

std::ostream& operator<<(std::ostream& os, Node& dn)
{
    os << *(dn.getStudent());
    return os;
}
