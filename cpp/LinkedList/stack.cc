using namespace std;

#include "list.cc"

template <typename T>
class Stack : public LinkedList<T> {
 public:
  int capacity;
  LinkedList<T> list;
  Stack(int cap) { this->capacity = cap; }

  void push(T data) {
    if (list.size() < capacity) {
      list.prepend(data);
      return;
    }
    cout << "Stack is full" << endl;
  }

  void pop() {
    if (list.size() > 0) {
      list.removeHead();
      return;
    }
    cout << "Stack is empty" << endl;
  }

  T top() {
    if (list.size() > 0) {
      return list.getHead()->data;
    }
    cout << "Stack is empty" << endl;
    return (T)NULL;
  }

  inline int size() { return list.size(); }

  inline bool isEmpty() { return list.size() == 0; }

  inline bool isFull() { return list.size() == capacity; }

  ostream &operator<<(ostream &os) {
    os << list << endl;
    return os;
  }
};
