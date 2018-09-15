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
    ncount = ncount - 1;
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
  void LinkedList::swap(Node* A, Node* B)
  {
    //set a handful of temporary pointers
    Node* Am = A->getPrev();
    Node* Ap = A->getNext();
    Node* Bm = B->getPrev();
    Node* Bp = B->getNext();

    //swap the outgoing pointers of A and B
    A->setPrev(Bm);
    A->setNext(Bp);
    B->setPrev(Am);
    B->setNext(Ap);

    //check if the ingoing pointers are valid
    //if so:
    //swap them
    if(Am != nullptr)
    {
      Am->setNext(B);
    }
    if(Ap != nullptr)
    {
      Ap->setPrev(B);
    }
    if(Bm != nullptr)
    {
      Bm->setNext(A);
    }
    if(Bp != nullptr)
    {
      Bp->setPrev(A);
    }

    //check if either node was the head or getTail
    //if so, set the new node to be head or tail
    if(this->getHead() == A)
    {
      this->head = B;
    }
    else if(this->getHead() == B)
    {
      this->head = A;
    }
    if(this->getTail() == A)
    {
      this->tail = B;
    }
    else if(this->getTail() == B)
    {
      this->tail = A;
    }

  }

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
      std::cout << "sorted looping" << std::endl;
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
          swap(curr, curr->getNext());
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
