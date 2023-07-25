using namespace std;

#include <iostream>
#include <vector>

template <typename T>
class Node {
 public:
  T data;
  Node* next;

  Node(T d) {
    this->data = d;
    this->next = NULL;
  }
};

template <typename T>
class LinkedList {
 public:
  Node<T>* head;

  LinkedList() { this->head = NULL; }

  Node<T>* getHead() {
    if (!head) {
      return (Node<T>*)NULL;
    }
    return head;
  }

  Node<T>* getTail() {
    if (!head) {
      return (Node<T>*)NULL;
    }
    Node<T>* lastNode = head;
    while (lastNode->next) {
      lastNode = lastNode->next;
    }
    return lastNode;
  }

  void prepend(T d) {
    Node<T>* newNode = new Node<T>(d);
    newNode->next = head;
    head = newNode;
  }

  void append(T d) {
    Node<T>* newNode = new Node<T>(d);

    if (!head) {
      head = newNode;
      return;
    }

    Node<T>* lastNode = head;
    while (lastNode->next) {
      lastNode = lastNode->next;
    }

    lastNode->next = newNode;
  }

  void insertBetween(T data, T before, T after) {
    Node<T>* prevNode = head;
    Node<T>* nextNode = head;

    Node<T>* newNode = new Node<T>(data);

    while (prevNode->data != after) {
      prevNode = prevNode->next;
    }

    while (nextNode->data != before) {
      nextNode = nextNode->next;
    }

    prevNode->next = newNode;
    newNode->next = nextNode;
  }

  void deleteHead() {
    Node<T>* curr = head;
    if (curr) {
      head = curr->next;
      curr = NULL;
      delete curr;
      return;
    }
  }

  void deleteTail() {
    if (!head) {
      return;
    }
    if (!head->next) {
      head = NULL;
      delete head;
      return;
    }

    Node<T>* prevNode = head;

    while (prevNode->next->next) {
      prevNode = prevNode->next;
    }
    prevNode->next = NULL;
    delete prevNode->next;
  }

  void deleteAny(T target) {
    Node<T>* curr = head;

    if (curr && curr->data == target) {
      head = curr->next;
      curr = NULL;
      delete curr;
      return;
    }

    Node<T>* prevNode = NULL;

    while (curr) {
      if (curr->data == target) {
        break;
      }
      prevNode = curr;
      curr = curr->next;
    }

    if (!curr) {
      return;
    }

    prevNode->next = curr->next;
    curr = NULL;
    delete curr;
  }

  int size() {
    int count = 0;
    Node<T>* curr = head;
    while (curr) {
      count++;
      curr = curr->next;
    }
    return count;
  }

  void reverseList() {
    Node<T>* prev = NULL;
    Node<T>* curr = head;
    Node<T>* nxt = NULL;
    while (curr) {
      nxt = curr->next;
      curr->next = prev;
      prev = curr;
      curr = nxt;
    }
    head = prev;
  }

  Node<T>* find(T target) {
    Node<T>* curr = head;
    Node<T>* toReturn = NULL;
    bool found = false;

    while (curr) {
      if (curr->data == target) {
        found = true;
        toReturn = curr;
        break;
      }
      curr = curr->next;
    }

    return (found) ? curr : (Node<T>*)NULL;
  }

  void printList() {
    Node<T>* curr = head;
    while (curr) {
      cout << curr->data << " ";
      curr = curr->next;
    }
    cout << endl;
  }

  void clear() {
    Node<T>* curr = head;
    Node<T>* nxt = NULL;
    while (curr) {
      nxt = curr->next;
      curr = NULL;
      delete curr;
      curr = nxt;
    }
    head = NULL;
  }
};
