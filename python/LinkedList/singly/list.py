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
