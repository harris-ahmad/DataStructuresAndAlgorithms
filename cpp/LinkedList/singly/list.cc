#include <iostream>
#include <memory>

template <typename T>
class Node
{
public:
    T data;
    std::shared_ptr<Node<T>> next;

    Node(T d) : data(d), next(nullptr) {}
};

template <typename T>
class LinkedList
{
public:
    LinkedList() : head(nullptr) {}

    std::shared_ptr<Node<T>> getHead() const
    {
        return head;
    }

    std::shared_ptr<Node<T>> getTail() const
    {
        auto lastNode = head;
        while (lastNode && lastNode->next)
        {
            lastNode = lastNode->next;
        }
        return lastNode;
    }

    void prepend(T d)
    {
        auto newNode = std::make_shared<Node<T>>(d);
        newNode->next = head;
        head = newNode;
    }

    void append(T d)
    {
        auto newNode = std::make_shared<Node<T>>(d);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            auto lastNode = getTail();
            lastNode->next = newNode;
        }
    }

    void insertBetween(T data, T before, T after)
    {
        auto newNode = std::make_shared<Node<T>>(data);
        auto prevNode = head;

        while (prevNode && prevNode->data != after)
        {
            prevNode = prevNode->next;
        }

        if (prevNode)
        {
            newNode->next = prevNode->next;
            prevNode->next = newNode;
        }
    }

    void deleteHead()
    {
        if (head)
        {
            head = head->next;
        }
    }

    void deleteTail()
    {
        if (!head)
        {
            return;
        }
        if (!head->next)
        {
            head = nullptr;
        }
        else
        {
            auto prevNode = head;
            while (prevNode->next && prevNode->next->next)
            {
                prevNode = prevNode->next;
            }
            prevNode->next = nullptr;
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
            head = head->next;
        }
        else
        {
            auto prevNode = head;
            auto curr = head->next;

            while (curr && curr->data != target)
            {
                prevNode = curr;
                curr = curr->next;
            }

            if (curr)
            {
                prevNode->next = curr->next;
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
        std::shared_ptr<Node<T>> prev = nullptr;
        auto curr = head;
        while (curr)
        {
            auto next = curr->next;
            curr->next = prev;
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
    }

    friend std::ostream &operator<<(std::ostream &output, const LinkedList &list)
    {
        auto curr = list.head;
        while (curr)
        {
            output << curr->data << " ";
            curr = curr->next;
        }
        return output;
    }

    friend std::istream &operator>>(std::istream &input, LinkedList &list)
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

private:
    std::shared_ptr<Node<T>> head;
};

int main()
{
    LinkedList<int> list;

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