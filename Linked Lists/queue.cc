using namespace std;

#include "list.cc"

template <typename T>
class Queue : public LinkedList<T> {
 public:
  int capacity;
  LinkedList<T> list;

  Queue(int cap) { this->capacity = cap; }

  void enqueue(T data) {
    if (list.size() < capacity) {
      list.append(data);
      return;
    }
    cout << "Queue is full" << endl;
  }

  void dequeue() {
    if (list.size() > 0) {
      list.removeHead();
      return;
    }
    cout << "Queue is empty" << endl;
  }

  T front() {
    if (list.size() > 0) {
      return list.getHead()->data;
    }
    cout << "Queue is empty" << endl;
    return (T)NULL;
  }

  T back() {
    if (list.size() > 0) {
      return list.getTail()->data;
    }
    cout << "Queue is empty" << endl;
    return (T)NULL;
  }

  inline int size() { return list.size(); }

  inline bool isEmpty() { return list.size() == 0; }

  inline bool isFull() { return list.size() == capacity; }

  inline void print() { list.print(); }
};