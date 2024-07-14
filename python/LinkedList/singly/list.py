class Node:
    """
    Node class representing a single node in a singly linked list.
    """

    def __init__(self, data):
        """
        Create a Node.

        :param data: The data to be stored in the node.
        """
        self.data = data
        self.next = None


class LinkedList:
    """
    LinkedList class representing a singly linked list.
    """

    def __init__(self):
        """
        Create an empty LinkedList.
        """
        self.head = None
        self.tail = None
        self.length = 0
        self.node_map = {}  # Dictionary for O(1) lookups

    def get_head(self):
        """
        Get the head node of the list.

        :return: The head node or None if the list is empty.
        """
        return self.head

    def get_tail(self):
        """
        Get the tail node of the list.

        :return: The tail node or None if the list is empty.
        """
        return self.tail

    def prepend(self, data):
        """
        Prepend a node to the beginning of the list.

        :param data: The data to be stored in the new node.
        """
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.next = self.head
            self.head = new_node
        self.node_map[data.id] = new_node
        self.length += 1

    def append(self, data):
        """
        Append a node to the end of the list.

        :param data: The data to be stored in the new node.
        """
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            self.tail = new_node
        else:
            self.tail.next = new_node
            self.tail = new_node
        self.node_map[data.id] = new_node
        self.length += 1

    def insert_between(self, data, before, after):
        """
        Insert a node between two existing nodes in the list.

        :param data: The data to be stored in the new node.
        :param before: The data of the node before which to
                       insert the new node.
        :param after: The data of the node after which to insert the new node.
        """
        new_node = Node(data)
        curr = self.head

        while curr and curr.data != after:
            curr = curr.next

        if curr and curr.next and curr.next.data == before:
            new_node.next = curr.next
            curr.next = new_node
            self.node_map[data.id] = new_node
            self.length += 1

    def delete_head(self):
        """
        Delete the head node of the list.
        """
        if self.head:
            self.node_map.pop(self.head.data.id, None)
            self.head = self.head.next
            if not self.head:
                self.tail = None
            self.length -= 1

    def delete_tail(self):
        """
        Delete the tail node of the list.
        """
        if not self.head:
            return
        if not self.head.next:
            self.node_map.pop(self.head.data.id, None)
            self.head = None
            self.tail = None
        else:
            prev_node = self.head
            while prev_node.next and prev_node.next.next:
                prev_node = prev_node.next
            self.node_map.pop(prev_node.next.data.id, None)
            prev_node.next = None
            self.tail = prev_node
        self.length -= 1

    def delete_any(self, target):
        """
        Delete any node from the list that matches the given target data.

        :param target: The target data to match for deletion.
        """
        if not self.head:
            return

        if self.head.data.id == target.id:
            self.node_map.pop(self.head.data.id, None)
            self.head = self.head.next
            if not self.head:
                self.tail = None
            self.length -= 1
        else:
            prev_node = self.head
            curr = self.head.next

            while curr and curr.data.id != target.id:
                prev_node = curr
                curr = curr.next

            if curr:
                prev_node.next = curr.next
                if not curr.next:
                    self.tail = prev_node
                self.node_map.pop(curr.data.id, None)
                self.length -= 1

    def size(self):
        """
        Get the size of the list.

        :return: The number of nodes in the list.
        """
        return self.length