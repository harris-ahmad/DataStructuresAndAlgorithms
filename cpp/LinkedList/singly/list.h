# ifndef LIST_H
# define LIST_H

#include <iostream>
#include <memory>

template <typename T>
class Node {
public:
    T data;
    std::shared_ptr<Node<T>> next;

    Node(T d) : data(d), next(nullptr) {}
};

template <typename T>
class LinkedList {
public:
    LinkedList() : head(nullptr) {}

    std::shared_ptr<Node<T>> getHead() const {
        return head;
    }

    std::shared_ptr<Node<T>> getTail() const {
        auto lastNode = head;
        while (lastNode && lastNode->next) {
            lastNode = lastNode->next;
        }
        return lastNode;
    }

    void prepend(T d) {
        auto newNode = std::make_shared<Node<T>>(d);
        newNode->next = head;
        head = newNode;
    }

    void append(T d) {
        auto newNode = std::make_shared<Node<T>>(d);
        if (!head) {
            head = newNode;
        } else {
            auto lastNode = getTail();
            lastNode->next = newNode;
        }
    }

    void insertBetween(T data, T before, T after) {
        auto newNode = std::make_shared<Node<T>>(data);
        auto prevNode = head;

        while (prevNode && prevNode->data != after) {
            prevNode = prevNode->next;
        }

        if (prevNode) {
            newNode->next = prevNode->next;
            prevNode->next = newNode;
        }
    }

    void deleteHead() {
        if (head) {
            head = head->next;
        }
    }

    void deleteTail() {
        if (!head) {
            return;
        }
        if (!head->next) {
            head = nullptr;
        } else {
            auto prevNode = head;
            while (prevNode->next && prevNode->next->next) {
                prevNode = prevNode->next;
            }
            prevNode->next = nullptr;
        }
    }

    void deleteAny(T target) {
        if (!head) {
            return;
        }

        if (head->data == target) {
            head = head->next;
        } else {
            auto prevNode = head;
            auto curr = head->next;

            while (curr && curr->data != target) {
                prevNode = curr;
                curr = curr->next;
            }

            if (curr) {
                prevNode->next = curr->next;
            }
        }
    }

    int size() const {
        int count = 0;
        auto curr = head;
        while (curr) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    void reverseList() {
        std::shared_ptr<Node<T>> prev = nullptr;
        auto curr = head;
        while (curr) {
            auto next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    std::shared_ptr<Node<T>> find(T target) const {
        auto curr = head;
        while (curr) {
            if (curr->data == target) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    void clear() {
        head = nullptr;
    }

    friend std::ostream& operator<<(std::ostream& output, const LinkedList& list) {
        auto curr = list.head;
        while (curr) {
            output << curr->data << " ";
            curr = curr->next;
        }
        return output;
    }

    friend std::istream& operator>>(std::istream& input, LinkedList& list) {
        T data;
        input >> data;
        list.append(data);
        return input;
    }

    void operator[](int index) const {
        auto curr = head;
        int count = 0;
        while (curr) {
            if (count == index) {
                std::cout << curr->data << std::endl;
                return;
            }
            count++;
            curr = curr->next;
        }
        std::cout << "Index out of bounds" << std::endl;
    }

private:
    std::shared_ptr<Node<T>> head;
};

#endif