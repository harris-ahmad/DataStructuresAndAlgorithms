package main

import (
	"fmt"
	DoublyLinkedList "github.com/harris-ahmad/DataStructuresAndAlgorithms/go/LinkedList/doubly"
)

func main() {
	dll := DoublyLinkedList{}

	// Test appending and prepending
	fmt.Println("Testing append and prepend:")
	dll.Append(1)
	dll.Append(2)
	dll.Append(3)
	dll.Prepend(0)
	dll.PrintList() // Expected Output: 0 1 2 3

	// Test inserting between nodes
	fmt.Println("Testing insert between:")
	dll.InsertBetween(1.5, 1)
	dll.PrintList() // Expected Output: 0 1 1.5 2 3

	// Test deleting head
	fmt.Println("Testing delete head:")
	dll.DeleteHead()
	dll.PrintList() // Expected Output: 1 1.5 2 3

	// Test deleting tail
	fmt.Println("Testing delete tail:")
	dll.DeleteTail()
	dll.PrintList() // Expected Output: 1 1.5 2

	// Test deleting any node
	fmt.Println("Testing delete any:")
	dll.DeleteAny(1.5)
	dll.PrintList() // Expected Output: 1 2

	// Test reversing the list
	fmt.Println("Testing reverse list:")
	dll.Reverse()
	dll.PrintList() // Expected Output: 2 1

	dll.Clear()
	dll.Append(1)

	// Test finding a node
	fmt.Println("Testing find:")
	node := dll.Find(1)
	if node != nil {
		fmt.Println(node.data) // Expected Output: 1
	} else {
		fmt.Println("Node not found")
	}

	// Test clearing the list
	fmt.Println("Testing clear:")
	dll.Clear()
	dll.PrintList() // Expected Output: (empty list)

	// Test reading a list
	fmt.Println("Testing read list:")
	dll.Append(10)
	dll.Append(20)
	dll.Append(30)
	dll.PrintList() // Expected Output: 10 20 30

	// Test size of the list
	fmt.Println("Testing size:")
	fmt.Println(dll.Size()) // Expected Output: 3
}
