class Node:
    """
    Node class representing a single node in stack.
    """

    def __init__(self, data: int, next=None):
        """
        Create a Node.

        :param data: The data to be stored in the node.
        """
        self.data = data
        self.next = next
     

class Stack:
    """
    LinkedList class representing a singly linked list.
    """
  
    def __init__(self) -> None:
        """
        Create an empty stack.
        """

        self.head = None
        
    def isEmpty(self) -> None:
        """
        Checks of stack is empty.
        
        :return: True if stack is empty and vice versa.
        """
        
        if self.head is None:
            return True
        else:
            return False

    def push(self, data: int) -> None:
        """
        Pushes an element at the top of the stack
        """
        
        if self.isEmpty():
            new = Node(data)
            self.head = new
            return
        
        new = Node(data, self.head)
        self.head = new

    def pop(self) -> int:
        """
        Pops and returns an element from the top of the stack

        :return: The data at top of the stack or None if stack is empty
        """
        
        if self.isEmpty():
            return -1
        
        data = self.head.data
        self.head = self.head.next

        return data
    
    def peak(self) -> int:
        """
        Returns an element from the top of the stack without popping

        :return: The data at top of the stack or None if stack is empty
        """
        
        if self.isEmpty():
            return -1
        
        return self.head.data
    
    def clear(self) -> None:
        """
        Clears the stack by popping all elements
        """
        
        while not self.isEmpty():
            self.pop()
            

if __name__ == "__main__":
    stack = Stack()

    # push 3 elements to stack
    stack.push(1)
    stack.push(2)
    stack.push(3)
    
    # pop elements
    print(stack.pop())      # -> 3
    print(stack.pop())      # -> 2

    # peak elements
    print(stack.peak())     # -> 1

    # clear stack
    stack.clear()

    # check if stack was cleared
    print(stack.peak())     # -> -1
