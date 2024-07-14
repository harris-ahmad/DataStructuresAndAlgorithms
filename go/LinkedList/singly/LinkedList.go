package main

import (
	"fmt"
)

// Node represents a single node in a singly linked list.
type Node struct {
	data interface{}
	next *Node
}

// LinkedList represents a singly linked list.
type LinkedList struct {
	head    *Node
	tail    *Node
	length  int
	nodeMap map[int]*Node // Map for O(1) lookups by ID
}

// NewLinkedList creates an empty LinkedList.
func NewLinkedList() *LinkedList {
	return &LinkedList{
		head:    nil,
		tail:    nil,
		length:  0,
		nodeMap: make(map[int]*Node),
	}
}

// Prepend adds a node to the beginning of the list.
func (ll *LinkedList) Prepend(id int, data interface{}) {
	newNode := &Node{data: data}
	if ll.head == nil {
		ll.head = newNode
		ll.tail = newNode
	} else {
		newNode.next = ll.head
		ll.head = newNode
	}
	ll.nodeMap[id] = newNode
	ll.length++
}

// Append adds a node to the end of the list.
func (ll *LinkedList) Append(id int, data interface{}) {
	newNode := &Node{data: data}
	if ll.head == nil {
		ll.head = newNode
		ll.tail = newNode
	} else {
		ll.tail.next = newNode
		ll.tail = newNode
	}
	ll.nodeMap[id] = newNode
	ll.length++
}

// InsertBetween inserts a node between two existing nodes in the list.
func (ll *LinkedList) InsertBetween(id int, data, before, after interface{}) {
	newNode := &Node{data: data}
	curr := ll.head

	for curr != nil && curr.data != after {
		curr = curr.next
	}

	if curr != nil && curr.next != nil && curr.next.data == before {
		newNode.next = curr.next
		curr.next = newNode
		ll.nodeMap[id] = newNode
		ll.length++
	}
}

// DeleteHead removes the head node of the list.
func (ll *LinkedList) DeleteHead() {
	if ll.head != nil {
		for k, v := range ll.nodeMap {
			if v == ll.head {
				delete(ll.nodeMap, k)
				break
			}
		}
		ll.head = ll.head.next
		if ll.head == nil {
			ll.tail = nil
		}
		ll.length--
	}
}

// DeleteTail removes the tail node of the list.
func (ll *LinkedList) DeleteTail() {
	if ll.head == nil {
		return
	}
	if ll.head.next == nil {
		for k, v := range ll.nodeMap {
			if v == ll.head {
				delete(ll.nodeMap, k)
				break
			}
		}
		ll.head = nil
		ll.tail = nil
	} else {
		prevNode := ll.head
		for prevNode.next != nil && prevNode.next.next != nil {
			prevNode = prevNode.next
		}
		for k, v := range ll.nodeMap {
			if v == prevNode.next {
				delete(ll.nodeMap, k)
				break
			}
		}
		prevNode.next = nil
		ll.tail = prevNode
	}
	ll.length--
}

// DeleteAny removes any node from the list that matches the given target ID.
func (ll *LinkedList) DeleteAny(id int) {
	if ll.head == nil {
		return
	}

	if node, ok := ll.nodeMap[id]; ok {
		if ll.head == node {
			ll.head = ll.head.next
			if ll.head == nil {
				ll.tail = nil
			}
			delete(ll.nodeMap, id)
			ll.length--
		} else {
			prevNode := ll.head
			curr := ll.head.next

			for curr != nil && curr != node {
				prevNode = curr
				curr = curr.next
			}

			if curr != nil {
				prevNode.next = curr.next
				if curr.next == nil {
					ll.tail = prevNode
				}
				delete(ll.nodeMap, id)
				ll.length--
			}
		}
	}
}

// Size returns the number of nodes in the list.
func (ll *LinkedList) Size() int {
	return ll.length
}

// ReverseList reverses the linked list in place.
func (ll *LinkedList) ReverseList() {
	var prev, curr, next *Node
	curr = ll.head
	ll.tail = ll.head

	for curr != nil {
		next = curr.next
		curr.next = prev
		prev = curr
		curr = next
	}
	ll.head = prev
}

// Find returns the node with the given ID.
func (ll *LinkedList) Find(id int) *Node {
	return ll.nodeMap[id]
}

// Clear removes all nodes from the list.
func (ll *LinkedList) Clear() {
	ll.head = nil
	ll.tail = nil
	ll.length = 0
	ll.nodeMap = make(map[int]*Node)
}

// PrintList prints the list data in a readable format.
func (ll *LinkedList) PrintList() {
	curr := ll.head
	for curr != nil {
		fmt.Printf("%v -> ", curr.data)
		curr = curr.next
	}
	fmt.Println("nil")
}

// Example usage
func main() {
	ll := NewLinkedList()

	// Adding data to the list
	ll.Append(1, "Node 1")
	ll.Append(2, "Node 2")
	ll.Append(3, "Node 3")

	// Printing the list
	fmt.Println("List after adding nodes:")
	ll.PrintList()

	// Deleting a node
	ll.DeleteAny(2)

	// Printing the list after deletion
	fmt.Println("List after deleting a node:")
	ll.PrintList()

	// Reversing the list
	ll.ReverseList()

	// Printing the reversed list
	fmt.Println("List after reversing:")
	ll.PrintList()
}
