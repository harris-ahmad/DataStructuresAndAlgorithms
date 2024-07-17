class Data:
    def __init__(self, id: int, value: int) -> None:
        self.id = id
        self.value = value

    def __repr__(self) -> str:
        return f"Data({self.id}, {self.value})"


class Node:
    def __init__(self, data: Data) -> None:
        self.data = data
        self.next = None
        self.prev = None

    def __repr__(self) -> str:
        return f"Node({self.data})"


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

    def prepend(self, data: Data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.next = self.head
            self.head.prev = new_node
            self.head = new_node
        self.length += 1
        self.node_map[data.id] = new_node

    def append(self, data: Data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            self.tail = new_node
        else:
            self.tail.next = new_node
            new_node.prev = self.tail
            self.tail = new_node
        self.length += 1
        self.node_map[data.id] = new_node

    def insert_between(self, data: Data, before: Data, after: Data):
        if before == after:
            raise Exception("Before and after nodes cannot be same")
        elif before == self.head.data:
            self.prepend(data)
            return
        elif after == self.tail.data:
            self.append(data)
            return

        new_node = Node(data)
        curr = self.head

        while curr and curr.data.value != after.value:
            curr = curr.next

        if curr and curr.next and curr.next.data.value == before.value:
            new_node.next = curr.next
            new_node.prev = curr
            curr.next.prev = new_node
            curr.next = new_node
            self.length += 1
            self.node_map[data.key] = new_node

    def delete_head(self):
        if self.head:
            self.node_map.pop(self.head.data.id, None)
            self.head = self.head.next
            if self.head:
                self.head.prev = None
            else:
                self.tail = None
            self.length -= 1
        else:
            raise Exception("List is empty")

    def delete_tail(self):
        if not self.head:
            raise Exception("List is empty")
        if not self.head.next:
            self.node_map.pop(self.head.data.id, None)
            self.head = None
            self.tail = None
        else:
            self.node_map.pop(self.tail.data.id, None)
            self.tail = self.tail.prev
            self.tail.next = None
        self.length -= 1

    def delete_any(self, target: Data):
        if not self.head:
            raise Exception("List is empty")

        if self.head.data == target:
            self.delete_head()
            return
        elif self.tail.data == target:
            self.delete_tail()
            return
        else:
            curr = self.head
            while curr and curr.data.id != target.id:
                curr = curr.next

            if curr:
                curr.prev.next = curr.next
                if curr.next:
                    curr.next.prev = curr.prev
                self.node_map.pop(target.id, None)
                self.length -= 1
