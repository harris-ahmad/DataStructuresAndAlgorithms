#include <iostream>
#include <assert.h>
#include "list.h"  // Adjust the include path as needed

void testPrepend() {
    LinkedList<int> list;
    list.prepend(1);
    assert(list.getHead()->data == 1);
    list.prepend(0);
    assert(list.getHead()->data == 0);
    assert(list.getHead()->next->data == 1);
    std::cout << "testPrepend passed!" << std::endl;
}

void testAppend() {
    LinkedList<int> list;
    list.append(1);
    assert(list.getTail()->data == 1);
    list.append(2);
    assert(list.getTail()->data == 2);
    std::cout << "testAppend passed!" << std::endl;
}

void testInsertBetween() {
    LinkedList<int> list;
    list.append(1);
    list.append(3);
    list.insertBetween(2, 3, 1);
    assert(list.getHead()->next->data == 2);
    assert(list.getHead()->next->next->data == 3);
    std::cout << "testInsertBetween passed!" << std::endl;
}

void testDeleteHead() {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.deleteHead();
    assert(list.getHead()->data == 2);
    std::cout << "testDeleteHead passed!" << std::endl;
}

void testDeleteTail() {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.deleteTail();
    assert(list.getTail()->data == 1);
    std::cout << "testDeleteTail passed!" << std::endl;
}

void testDeleteAny() {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.deleteAny(2);
    assert(list.getHead()->next->data == 3);
    std::cout << "testDeleteAny passed!" << std::endl;
}

void testSize() {
    LinkedList<int> list;
    assert(list.size() == 0);
    list.append(1);
    list.append(2);
    list.append(3);
    assert(list.size() == 3);
    std::cout << "testSize passed!" << std::endl;
}

void testReverseList() {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.reverseList();
    assert(list.getHead()->data == 3);
    assert(list.getTail()->data == 1);
    std::cout << "testReverseList passed!" << std::endl;
}

void testFind() {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    assert(list.find(2)->data == 2);
    assert(list.find(3) == nullptr);
    std::cout << "testFind passed!" << std::endl;
}

void testClear() {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.clear();
    assert(list.getHead() == nullptr);
    assert(list.size() == 0);
    std::cout << "testClear passed!" << std::endl;
}

int main() {
    testPrepend();
    testAppend();
    testInsertBetween();
    testDeleteHead();
    testDeleteTail();
    testDeleteAny();
    testSize();
    testReverseList();
    testFind();
    testClear();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
