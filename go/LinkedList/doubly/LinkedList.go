package main

import "fmt"

type Node struct {
	data interface{}
	next *Node
	prev *Node
}

type DoublyLinkedList struct {
	head   *Node
	tail   *Node
	length int
}

func NewNode(data interface{}) *Node {
	return &Node{data: data}
}

func NewDoublyLinkedList() *DoublyLinkedList {
	return &DoublyLinkedList{
		head:   nil,
		tail:   nil,
		length: 0,
	}
}

func (dll *DoublyLinkedList) Prepend(data interface{}) {
	newNode := NewNode(data)
	if dll.head == nil {
		dll.head = newNode
		dll.tail = newNode
	} else {
		newNode.next = dll.head
		dll.head.prev = newNode
		dll.head = newNode
	}
}

func (dll *DoublyLinkedList) Append(data interface{}) {
	newNode := NewNode(data)
	if dll.head == nil {
		dll.head = newNode
		dll.tail = newNode
	} else {
		newNode.prev = dll.tail
		dll.tail.next = newNode
		dll.tail = newNode
	}
}

func (dll *DoublyLinkedList) InsertBetween(data interface{}, after interface{}) {
	current := dll.head
	for current != nil && current.data != after {
		current = current.next
	}
	if current != nil {
		newNode := NewNode(data)
		newNode.next = current.next
		newNode.prev = current
		if current.next != nil {
			current.prev.next = newNode
		}
		current.next = newNode
		if newNode.next == nil {
			dll.tail = newNode
		}
	}
}

func (dll *DoublyLinkedList) DeleteHead() {
	if dll.head != nil {
		if dll.head.next != nil {
			dll.head = dll.head.next
			dll.head.prev = nil
		} else {
			dll.head = nil
			dll.tail = nil
		}
	}
}

func (dll *DoublyLinkedList) DeleteTail() {
	if dll.tail != nil {
		if dll.tail.prev != nil {
			dll.tail = dll.tail.prev
			dll.tail.next = nil
		} else {
			dll.head = nil
			dll.tail = nil
		}
	}
}

func (dll *DoublyLinkedList) DeleteAny(data interface{}) {
	current := dll.head
	for current != nil && current.data != data {
		current = current.next
	}
	if current != nil {
		if current.prev != nil {
			current.prev.next = current.next
		} else {
			dll.head = current.next
		}
		if current.next != nil {
			current.next.prev = current.prev
		} else {
			dll.tail = current.prev
		}
	}
}

func (dll *DoublyLinkedList) Size() int {
	count := 0
	current := dll.head
	for current != nil {
		count++
		current = current.next
	}
	return count
}

func (dll *DoublyLinkedList) Reverse() {
	current := dll.head
	var prev *Node
	dll.tail = current
	for current != nil {
		prev = current.prev
		current.prev = current.next
		current.next = prev
		if current.prev == nil {
			dll.head = current
		}
		current = current.prev
	}
}

func (dll *DoublyLinkedList) Find(data interface{}) *Node {
	current := dll.head
	for current != nil {
		if current.data == data {
			return current
		}
		current = current.next
	}
	return nil
}

func (dll *DoublyLinkedList) Clear() {
	dll.head = nil
	dll.tail = nil
}

func (dll *DoublyLinkedList) PrintList() {
	current := dll.head
	for current != nil {
		fmt.Print(current.data, " ")
		current = current.next
	}
	fmt.Println()
}

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
