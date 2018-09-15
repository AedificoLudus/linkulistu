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

  int LinkedList::getCount()
  {
    return ncount;
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

  void LinkedList::concatenate(LinkedList second)
  {
    Node* curr = second.getHead();
    while(curr != nullptr)
    {
      this->addToTail(*(curr->getStudent()));
      curr = curr->getNext();
    }
  }


  // Removers
  void LinkedList::deleteNode(Node *newNode)
  {
    if (newNode == nullptr) return;
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
    else
    {
      curr->getPrev()->setNext(curr->getNext());
      curr->getNext()->setPrev(curr->getPrev());
    }
    curr->~Node();
  }

  void LinkedList::remove(std::string Name)
  {
    Node* curr = findName(Name);
    while(curr != nullptr)
    {
      deleteNode(curr);
      curr = findName(Name);
    }
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
    while(curr->getStudent()->get_name() != Name)
    {
      // cout << curr->getStudent()->get_name() << endl;
      curr = curr->getNext();
      if(curr == nullptr) {return nullptr;}
    }
    return curr;
  }

  bool LinkedList::sorted()
  {
    Node* curr = this->getHead();
    while(curr != nullptr)
    {
      if(curr->getNext() != nullptr)
      {
        if((curr->getStudent()->get_name()).compare(curr->getNext()->getStudent()->get_name()) > 0)
        {
          return false;
        }
      }
      curr = curr->getNext();
    }
    return true;
  }

  void LinkedList::order()
  {
    Node* curr = this->getHead();
    while(sorted() == false)
    {
      if(curr->getNext() != nullptr)
      {
        if(curr->getStudent()->get_name().compare(curr->getNext()->getStudent()->get_name()))
        {
          std::cout << "swapping" <<std::endl;
          Node* before = curr->getPrev();
          Node* after = curr->getNext();
          if(before != NULL)
          {
            before->setNext(after);
          }
          curr->setNext(after->getNext());
          curr->setPrev(after);
          after->setNext(curr);
          after->setPrev(before);
        }
        else
        {
          curr = curr->getNext();
        }
      }
      else
      {
        curr = this->getHead();
      }
    }
  }

  // Misc.
  double LinkedList::sumList(Node* curr)
  {
      if (curr != nullptr)
      {
        return curr->getStudent()->get_score() + sumList(curr->getNext());
      }
      else
      {
        return 0;
      }
  }

  double LinkedList::calcAverage()
  {
    return (sumList(head))/ncount;
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
  void LinkedList::operator+=(LinkedList& rhs)
  {
    this->concatenate(rhs);
  }

  ostream& operator<<(std:: ostream& os, LinkedList& dl)
  {
      Node* curr = dl.getHead();
      while(curr != nullptr)
      {
        os << *curr << " ";
        curr = curr->getNext();
      }
      return os;
  }
