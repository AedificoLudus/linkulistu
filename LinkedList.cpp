//Course: SENG1120
//Coded by: Tom Williams
//Student Number: 3282012

#include <string>
#include <iostream>
#include "LinkedList.h"

  // Constructors
  LinkedList::LinkedList()
  {
    head = nullptr;
    tail = nullptr;
    ncount = 0;
  }

  // Empty Destructor
  LinkedList::~LinkedList(){}

  // Getters
  Node* LinkedList::getHead()
  {
    return head;
  }

  Node* LinkedList::getTail()
  {
    return tail;
  }

  // Adders
  void LinkedList::addFirst(Node* firstNode)
  {
    head = firstNode;
    tail = firstNode;
  }

  void LinkedList::addToHead(Student nstudent)
  {
    Node* newNode = new Node(nstudent);
    if(head == nullptr)
    {
      addFirst(newNode);
    } else {
      head->setPrev(newNode);
      newNode->setNext(head);
      head = newNode;
    }
    ncount += 1;
  }

  void LinkedList::addToTail(Student nstudent)
  {
    Node* newNode = new Node(nstudent);
    if (tail == nullptr) {
      addFirst(newNode);
    } else {
      newNode->setPrev(tail);
      tail->setNext(newNode);
      tail = newNode;
    }
    ncount += 1;
  }

  LinkedList* CloneList(LinkedList* CopyList, Node* curr, Student data)
  {
    if(CopyList == nullptr)
    {

    }
    //{
    //  copy = new LinkedList();
    //}
    //if(curr != nullptr)
    //{
    //  data.set_name(curr->getStudent()->get_name());
    //  data.set_score(curr->getStudent()->get_score());
    //  copy->addToTail(&data);
    //  curr = curr->getNext();
    //  Clone(copy, curr, data);
    //}
    return CopyList;
  }

  void LinkedList::concatenate(LinkedList second)
  {
      this->tail->setNext(second.getHead());
      second.getHead()->setPrev(this->tail);
  }


  // Removers
  void LinkedList::deleteNode(Node *newNode)
  {
    Node* curr = newNode;
    if(curr == head)
    {
      head = curr->getNext();
      if(curr == tail)
      {
        tail = nullptr;
      }
      else
      {
        curr->getNext()->setPrev(nullptr);
      }
    }
    else if(curr == tail)
    {
      tail = curr->getPrev();
      curr->getPrev()->setNext(nullptr);
    }
    curr->~Node();
  }

  void LinkedList::remove(std::string Name)
  {
    Node* curr = findName(Name);
    deleteNode(curr);
  }

  void LinkedList::empty()
  {
    if(head != nullptr)
    {
      deleteNode(head);
      empty();
    }
  }


  // Sorters
  Node* LinkedList::findName(std::string Name)
  {
    Node* curr = head;
    cout << "startname" << curr->getStudent()<< "endname" << endl;
    while(curr->getStudent()->get_name() != Name)
    {
      curr = curr->getNext();
    }
    return curr;
  }

  void LinkedList::sortName()
  {

  }

  void LinkedList::order()
  {
    this->sortName();
  }

  // Misc.
  double LinkedList::sumList(Node* curr)
  {
      if ( curr != nullptr )
          return curr->getStudent()->get_score() + sumList(curr->getNext());
      else
          return 0;
  }

  double LinkedList::calcAverage()
  {
    return sumList(head)/ncount;
  }

  int LinkedList::count(std::string searchName)
  {
    Node* curr = head;
    int num = 0;
    while(curr->getNext() != nullptr)
    {
      // cout << searchName << " " << curr->getStudent()->get_name() << endl;
      if(curr->getStudent()->get_name() == searchName)
      {
        num += 1;

      }
      curr = curr->getNext();
    }
    return num;
  }

// Overloaders
  LinkedList& LinkedList::operator+=(LinkedList& rhs)
  {
    this->concatenate(rhs);
  }

  ostream& operator<<(std:: ostream& os, LinkedList& dl)
  {
      Node* curr = dl.getHead();
      while(curr != nullptr)
      {
        os << curr << " ";
        curr = curr->getNext();
      }
      return os;
  }
