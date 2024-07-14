package main

import (
	"sync"
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
	nodeMap map[interface{}]*Node // Map for O(1) lookups
	mutex   sync.RWMutex          // Mutex for thread-safe operations
}

// NewLinkedList creates an empty LinkedList.
func NewLinkedList() *LinkedList {
	return &LinkedList{
		head:    nil,
		tail:    nil,
		length:  0,
		nodeMap: make(map[interface{}]*Node),
	}
}

// GetHead returns the head node of the list.
func (ll *LinkedList) GetHead() *Node {
	ll.mutex.RLock()
	defer ll.mutex.RUnlock()
	return ll.head
}

// GetTail returns the tail node of the list.
func (ll *LinkedList) GetTail() *Node {
	ll.mutex.RLock()
	defer ll.mutex.RUnlock()
	return ll.tail
}
