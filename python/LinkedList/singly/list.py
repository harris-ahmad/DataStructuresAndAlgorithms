import os
from typing import List, Dict

class Node: 
    def __init__(self, data):
        self.data = data
        self.next = None
        self._id = os.urandom(16).hex()
        
    def __repr__(self) -> str:
        return f"Node({self._id}: {self.data})"

class LinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.length = 0
        # dictionary to store nodes by their IDs for faster lookup and deletion
        self.node_map = {}

    def get_head(self):
        """Get the head node of the list."""
        return self.head

    def get_tail(self):
        """Get the tail node of the list."""
        return self.tail

    def prepend(self, data):
        """Prepend a node to the start of the list."""
        
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.next = self.head
            self.head = new_node
        self.node_map[new_node._id] = new_node.data
        self.length += 1

    def append(self, data):
        """Append a node to the end of the list."""
        
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            self.tail = new_node
        else:
            self.tail.next = new_node
            self.tail = new_node
        self.node_map[new_node._id] = new_node.data
        self.length += 1

    def insert_between(self, data, before, after):
        """
        Insert a node between two existing nodes in the list.

        :param data: The data to be stored in the new node.
        :param before: The data of the node before which to
                       insert the new node.
        :param after: The data of the node after which to insert the new node.
        """
        if not self.head:
            raise Exception("List is empty, nothing to insert")
        
        new_node = Node(data)
        curr = self.head

        while curr and curr.data != after:
            curr = curr.next

        if curr and curr.next and curr.next.data == before:
            new_node.next = curr.next
            curr.next = new_node
            self.node_map[new_node._id] = new_node.data
            self.length += 1

    def delete_head(self):
        """Delete the head node of the list."""
        
        if self.head:
            self.node_map.pop(self.head.data.id, None)
            self.head = self.head.next
            if not self.head:
                self.tail = None
            self.length -= 1
        else:
            raise Exception("List is empty, nothing to delete")

    def delete_tail(self):
        """
        Delete the tail node of the list.
        """
        if not self.head:
            raise Exception("List is empty, nothing to delete")
        
        if not self.head.next:
            self.node_map.pop(self.head._id, None)
            self.head = None
            self.tail = None
        else:
            prev_node = self.head
            while prev_node.next and prev_node.next.next:
                prev_node = prev_node.next
            self.node_map.pop(prev_node.next._id, None)
            prev_node.next = None
            self.tail = prev_node
        self.length -= 1

    def delete_any(self, target):
        """Delete any node from the list that matches the given target data."""
        
        if not self.head:
            raise Exception("List is empty, nothing to delete")

        if self.head._id == target._id:
            self.node_map.pop(self.head._id, None)
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
                self.node_map.pop(curr._id, None)
                self.length -= 1

    def size(self):
        """Get the number of nodes in the list."""
        
        return self.length

    def reverse_list(self):
        """
        Reverse the linked list in place.
        """
        
        prev = None
        curr = self.head
        next_node = None

        self.tail = self.head

        while curr:
            next_node = curr.next
            curr.next = prev
            prev = curr
            curr = next_node
        
        self.head = prev

    def find(self, node: Node):
        """
        Find a node in the list by its id.

        :param id: The id of the node to find.
        :return: The node with the given id or None if not found.
        """
        return self.node_map.get(node._id, None)

    def clear(self):
        """
        Clear the list.
        """
        self.head = None
        self.tail = None
        self.length = 0
        self.node_map = {}

    def print_list(self):
        """
        Print the list data in a readable format.
        """
        curr = self.head
        result = []
        while curr:
            result.append(str(curr.data))
            curr = curr.next
        print(" -> ".join(result))
        