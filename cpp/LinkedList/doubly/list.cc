#include <iostream>
#include <memory>

template <typename T>
class Node
{
public:
    T data;
    std::shared_ptr<Node<T>> next;
    std::weak_ptr<Node<T>> prev; // Added for doubly linked list

    Node(T d) : data(d), next(nullptr), prev() {}
};

template <typename T>
class DoublyLinkedList
{
private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    std::shared_ptr<Node<T>> getHead() const
    {
        return head;
    }

    std::shared_ptr<Node<T>> getTail() const
    {
        return tail;
    }

    void prepend(T d)
    {
        auto newNode = std::make_shared<Node<T>>(d);
        if (!head)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void append(T d)
    {
        auto newNode = std::make_shared<Node<T>>(d);
        if (!head)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void insertBetween(T data, T before, T after)
    {
        auto newNode = std::make_shared<Node<T>>(data);
        auto curr = head;

        while (curr && curr->data != after)
        {
            curr = curr->next;
        }

        if (curr)
        {
            auto nextNode = curr->next;
            newNode->next = nextNode;
            newNode->prev = curr;
            curr->next = newNode;
            if (nextNode)
            {
                nextNode->prev = newNode;
            }
            else
            {
                tail = newNode;
            }
        }
    }

    void deleteHead()
    {
        if (head)
        {
            head = head->next;
            if (head)
            {
                head->prev.reset();
            }
            else
            {
                tail = nullptr;
            }
        }
    }

    void deleteTail()
    {
        if (!tail)
        {
            return;
        }
        if (tail == head)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tail = tail->prev.lock();
            if (tail)
            {
                tail->next = nullptr;
            }
        }
    }

    void deleteAny(T target)
    {
        if (!head)
        {
            return;
        }

        if (head->data == target)
        {
            deleteHead();
        }
        else if (tail->data == target)
        {
            deleteTail();
        }
        else
        {
            auto curr = head;

            while (curr && curr->data != target)
            {
                curr = curr->next;
            }

            if (curr)
            {
                auto prevNode = curr->prev.lock();
                auto nextNode = curr->next;

                if (prevNode)
                {
                    prevNode->next = nextNode;
                }
                if (nextNode)
                {
                    nextNode->prev = prevNode;
                }
            }
        }
    }

    int size() const
    {
        int count = 0;
        auto curr = head;
        while (curr)
        {
            count++;
            curr = curr->next;
        }
        return count;
    }

    void reverseList()
    {
        auto curr = head;
        std::shared_ptr<Node<T>> prev = nullptr;
        tail = head;

        while (curr)
        {
            auto next = curr->next;
            curr->next = prev;
            curr->prev = next;
            prev = curr;
            curr = next;
        }

        head = prev;
    }

    std::shared_ptr<Node<T>> find(T target) const
    {
        auto curr = head;
        while (curr)
        {
            if (curr->data == target)
            {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    void clear()
    {
        head = nullptr;
        tail = nullptr;
    }

    friend std::ostream &operator<<(std::ostream &output, const DoublyLinkedList &list)
    {
        auto curr = list.head;
        while (curr)
        {
            output << curr->data << " ";
            curr = curr->next;
        }
        return output;
    }

    friend std::istream &operator>>(std::istream &input, DoublyLinkedList &list)
    {
        T data;
        input >> data;
        list.append(data);
        return input;
    }

    void operator[](int index) const
    {
        auto curr = head;
        int count = 0;
        while (curr)
        {
            if (count == index)
            {
                std::cout << curr->data << std::endl;
                return;
            }
            count++;
            curr = curr->next;
        }
        std::cout << "Index out of bounds" << std::endl;
    }
};

int main()
{
    DoublyLinkedList<int> list;

    list.append(10);
    list.append(20);
    list.append(30);
    list.append(40);

    list.prepend(5);

    list.insertBetween(25, 30, 20);

    std::cout << "List after appending, prepending, and inserting elements: ";
    std::cout << list << std::endl;

    std::cout << "Head of the list: " << list.getHead()->data << std::endl;
    std::cout << "Tail of the list: " << list.getTail()->data << std::endl;

    auto foundNode = list.find(25);
    if (foundNode)
    {
        std::cout << "Found element 25 in the list." << std::endl;
    }
    else
    {
        std::cout << "Element 25 not found in the list." << std::endl;
    }

    list.deleteHead();
    std::cout << "List after deleting the head: ";
    std::cout << list << std::endl;

    list.deleteTail();
    std::cout << "List after deleting the tail: ";
    std::cout << list << std::endl;

    list.deleteAny(25);
    std::cout << "List after deleting element 25: ";
    std::cout << list << std::endl;

    list.reverseList();
    std::cout << "List after reversing: ";
    std::cout << list << std::endl;

    std::cout << "Size of the list: " << list.size() << std::endl;

    list.clear();
    std::cout << "List after clearing: ";
    std::cout << list << std::endl;

    return 0;
}