package doubly

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
