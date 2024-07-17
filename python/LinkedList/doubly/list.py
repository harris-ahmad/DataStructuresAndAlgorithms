class Data:
    def __init__(self, key, value) -> None:
        self.key = key
        self.value = value


class Node:
    def __init__(self, data: Data) -> None:
        self.data = data
        self.next = None
        self.prev = None


class DoublyLinkedList:
    def __init__(self) -> None:
        self.head: Node | None = None
        self.tail: Node | None = None
        self.length: int = 0
        self.node_map: dict[int, Node] = {}

    def get_head(self):
        return self.head

    def get_tail(self):
        return self.tail

    def prepend(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.next = self.head
            self.head.prev = new_node
            self.head = new_node
        self.length += 1
        self.node_map[data.key] = new_node

    def insert_between(self, data, before, after):
        new_node = Node(data)
        curr = self.head

        while curr and curr.data.value != before:
            curr = curr.next

        if curr and curr.next and curr.next.data.value == before:
            new_node.next = curr.next
            new_node.prev = curr
            curr.next.prev = new_node
            curr.next = new_node
            self.length += 1
            self.node_map[data.key] = new_node
