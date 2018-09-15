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
    //this doesn't increment the node count because it's only ever called from addToHead or addToTail
  }

  void LinkedList::addToHead(Student nstudent)
  {
    //make the new Node
    Node* newNode = new Node(nstudent);
    //if the list is empty
    if(head == nullptr)
    {
      addFirst(newNode);
    } else {
      //add the node before the head
      head->setPrev(newNode);
      newNode->setNext(head);
      //make the node the new head
      head = newNode;
    }
    //increment the node count
    ncount += 1;
  }

  void LinkedList::addToTail(Student nstudent)
  {
    //make the new Node
    Node* newNode = new Node(nstudent);
    //if the list is empty
    if (tail == nullptr) {
      addFirst(newNode);
    } else {
      //add the node after the tail
      newNode->setPrev(tail);
      tail->setNext(newNode);
      //make the node the new tail
      tail = newNode;
    }
    //increment the node count
    ncount += 1;
  }

  void LinkedList::concatenate(LinkedList second)
  {
    //set curr to the head of the second list
    Node* curr = second.getHead();
    while(curr != nullptr)
    {
      //add a node to the tail of the first list copied from the data of the second
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
      //if the node is the only node
      if(curr == tail)
      {
        //empty the list
        head = nullptr;
        tail = nullptr;
      }
      else
      {
        //remove the Prev link from the next node
        curr->getNext()->setPrev(nullptr);
      }
    }
    else if(curr == tail)
    {
      //set the tail to the node before
      tail = curr->getPrev();
      curr->getPrev()->setNext(nullptr);
    }
    else
    {
      //set the incoming pointers to each other
      curr->getPrev()->setNext(curr->getNext());
      curr->getNext()->setPrev(curr->getPrev());
    }
    //delete the node
    curr->~Node();
    //decrement the node count
    ncount = ncount - 1;
  }

  void LinkedList::remove(std::string Name)
  {
    //find the first instance of that name from the list
    Node* curr = findName(Name);
    //while findName is still finding instances of that name
    while(curr != nullptr)
    {
      //remove the offending node
      deleteNode(curr);
      //check there aren't still more instances
      curr = findName(Name);
    }
  }

  void LinkedList::empty()
  {
    if(head != nullptr)
    {
      //delete the head
      deleteNode(this->head);
      //recursively delete the list
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
    //set the head of the list to current
    Node* curr = this->getHead();
    //while the current node is a valid node
    while(curr != this->getTail())
    {
      //if the current node is a valid node
      if(curr->getNext() != nullptr)
      {
        std::string tempStringCurr = curr->getStudent()->get_name();
        std::string tempStringNext = curr->getNext()->getStudent()->get_name();
        //if the current name should be after the next name
        if(tempStringCurr.compare(tempStringNext) > 0)
        {
          return false;
        }
      }
      //increment current
      curr = curr->getNext();
      std::cout << "returning true" << std::endl;
      return true;
    }
    //we've now reached the end of the list without returning false
    //therefore the list is sorted
    return true;
  }

  void LinkedList::order()
  {
    Node* curr = this->getHead();
    while(sorted() == false)
    {
      //if we're not at the end of the list
      if(curr->getNext() != nullptr)
      {
        std::string tempStringCurr = curr->getStudent()->get_name();
        std::string tempStringNext = curr->getNext()->getStudent()->get_name();
        //if the next name is meant to be before the current
        if(tempStringCurr.compare(tempStringNext) > 0)
        {
          //swap those two nodes
          swap(curr, curr->getNext());
        }
        else
        {
          //otherwise, increment the current node
          curr = curr->getNext();
        }
      }
      else
      {
        //when ew reach the end of the list, move back to the start
        curr = this->getHead();
      }
    }
  }

  // Misc.
  double LinkedList::sumList(Node* curr)
  {
      if (curr != nullptr)
      {
        //recursively add the students score
        return curr->getStudent()->get_score() + sumList(curr->getNext());
      }
      else
      {
        //when we reach the end of the list, return 0
        return 0;
      }
  }

  double LinkedList::calcAverage()
  {
    //divide the sum of the list by the number of nodes
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
