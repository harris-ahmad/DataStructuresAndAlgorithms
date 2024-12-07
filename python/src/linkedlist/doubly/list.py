class Node:
    def __init__(self, data) -> None:
        self.data = data
        self.next = None
        self.prev = None


class DoublyLinkedList:
    def __init__(self) -> None:
        self.head = None
        self.tail = None

    def get_head(self):
        return self.head

    def get_tail(self):
        return self.tail

    def prepend(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.next = self.head
            self.head.prev = new_node
            self.head = new_node

    def append(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.prev = self.tail
            self.tail.next = new_node
            self.tail = new_node

    def insert_between(self, data, after_data):
        new_node = Node(data)
        current = self.head
        while current and current.data != after_data:
            current = current.next
        if current:
            new_node.next = current.next
            new_node.prev = current
            if current.next:
                current.next.prev = new_node
            current.next = new_node
            if new_node.next is None:
                self.tail = new_node

    def delete_head(self):
        if not self.head:
            raise Exception("List is empty, nothing to delete")
        else:
            self.head = self.head.next
            if self.head:
                self.head.prev = None
            else:
                self.tail = None

    def delete_tail(self):
        if not self.head or not self.tail:
            raise Exception("List is empty, nothing to delete")
        else:
            if self.tail:
                if self.tail.prev:
                    self.tail = self.tail.prev
                    self.tail.next = None
                else:
                    self.head = self.tail = None

    def delete_any(self, target):
        current = self.head
        while current and current.data != target:
            current = current.next
        if not current:
            raise Exception("Target not found")
        else:
            if current.prev:
                current.prev.next = current.next
            else:
                self.head = current.next
            if current.next:
                current.next.prev = current.prev
            else:
                self.tail = current.prev

    def find(self, data):
        current = self.head
        while current:
            if current.data == data:
                return current
            current = current.next
        return None

    def clear(self):
        current = self.head
        while current:
            next_node = current.next
            current = next_node
        self.head = None
        self.tail = None

    def reverse_list(self):
        current = self.head
        prev = None
        while current:
            next_node = current.next
            current.next = prev
            current.prev = next_node
            prev = current
            current = next_node
        self.head = prev
        if self.head:
            self.tail = self.head
            while self.tail.next:
                self.tail = self.tail.next

    def __repr__(self):
        if not self.head or not self.tail:
            raise Exception("List is empty, nothing to print")
        current = self.head
        output = ""
        while current:
            output += f'{str(current.data)} '
            current = current.next
        return output

    def __len__(self):
        count = 0
        current = self.head
        while current:
            count += 1
            current = current.next
        return count


def main():
    dll = DoublyLinkedList()

    # Test appending and prepending
    print("Testing append and prepend:")
    for i in range(1, 10):
        dll.append(i)
    for i in range(30, 20, -1):
        dll.prepend(i)
    print(dll)  # Expected Output: 0 1 2 3

    # Test inserting between nodes
    print("Testing insert_between:")
    dll.insert_between(1.5, 1)
    print(dll)  # Expected Output: 0 1 1.5 2 3

    # Test deleting head
    print("Testing delete_head:")
    dll.delete_head()
    print(dll)  # Expected Output: 1 1.5 2 3

    # Test deleting tail
    print("Testing delete_tail:")
    dll.delete_tail()
    print(dll)

    print("Testing delete_any:")
    dll.delete_any(2)
    print(dll)

    print("Testing __len__:")
    print(len(dll))

    print("Testing reverse:")
    dll.reverse_list()
    print(dll)


main()
