import os
from typing import Dict, Optional, Any

class Node: 
    def __init__(self, data: Any):
        self.data = data
        self.next: Optional["Node"] = None
        self._id = os.urandom(16).hex()
        
    def __repr__(self) -> str:
        return f"Node({self._id}: {self.data})"

class LinkedList:
    def __init__(self):
        self.head: Optional[Node] = None
        self.tail: Optional[Node] = None
        self.length: int = 0
        # dictionary to store nodes by their IDs for faster lookup and deletion
        self.node_map: Dict[str, Node] = {}

    def get_head(self) -> Optional[Node]:
        """Get the head node of the list."""
        return self.head

    def get_tail(self) -> Optional[Node]: 
        """Get the tail node of the list."""
        return self.tail

    def prepend(self, data: Any) -> None:
        """Prepend a node to the start of the list."""
        
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node
        
        if not self.tail:
            self.tail = new_node
        
        self.node_map[new_node._id] = new_node.data
        self.length += 1

    def append(self, data):
        """Append a node to the end of the list."""
        
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            self.tail = new_node
        else:
            assert self.tail is not None, "Tail node is not set"
            
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
        
        if not self.head:
            raise Exception("List is empty, nothing to delete")
        self.node_map.pop(self.head._id, None)
        self.head = self.head.next
        if not self.head:
            self.tail = None
        self.length -= 1

    def delete_tail(self):
        """
        Delete the tail node of the list.
        """
        if not self.head:
            raise Exception("List is empty, nothing to delete")
        
        if not self.head.next or self.head == self.tail:
            self.node_map.pop(self.head._id, None)
            self.head = self.tail = None
        else:
            prev_node = self.head
            while prev_node.next != self.tail:
                prev_node = prev_node.next
            self.node_map.pop(self.tail._id, None)
            self.tail = prev_node
            self.tail.next = None
            
        self.length -= 1

    def delete_any(self, target: Node):
        """Delete any node from the list that matches the given target data."""
        if not isinstance(target, Node):
            raise ValueError("Target must be a Node instance")
        
        if target._id not in self.node_map:
            raise Exception(f"Node with ID {target._id} not found in the list")
        
        if self.head._id == target._id:
            self.delete_head()
            return
        else:
            prev_node: Node = self.head
            curr: Node = self.head.next

            while curr and curr._id != target._id:
                prev_node = curr
                curr = curr.next

            if curr:
                prev_node.next = curr.next
                if not curr.next:
                    self.tail = prev_node
                self.node_map.pop(curr._id, None)
                self.length -= 1
            else:
                raise Exception(f"Node with ID {target._id} not found in the list")

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

    def find(self, node: Node) -> Optional[Node]:
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
        self.node_map.clear()
        
    def __len__(self) -> int:
        return self.length
    
    def __iter__(self):
        current = self.head
        while current:
            yield current
            current = current.next
            
    def __repr__(self) -> str:
        nodes = [str(node) for node in self]
        return " -> ".join(nodes)

    def print_list(self):
        """
        Print the list data in a readable format. Since we have a 
        custom __iter__ and __repr__ methods, this method is not necessary. Simply
        use a print statement to print the list data.
        """
        print(self)