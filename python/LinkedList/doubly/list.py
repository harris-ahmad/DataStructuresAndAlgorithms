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
        new_node = self.create_node(data)
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
