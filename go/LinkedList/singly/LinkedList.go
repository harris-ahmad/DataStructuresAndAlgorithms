package main

import (
	"fmt"
	"sync"
)

type Node struct {
	data interface{}
	next *Node
}

type LinkedList struct {
	head    *Node
	tail    *Node
	length  int
	nodeMap map[interface{}]*Node // Map for O(1) lookups
	mutex   sync.RWMutex          // Mutex for thread-safe operations
}

func NewLinkedList() *LinkedList {
	return &LinkedList{
		head:    nil,
		tail:    nil,
		length:  0,
		nodeMap: make(map[interface{}]*Node),
	}
}

func (ll *LinkedList) GetHead() *Node {
	ll.mutex.RLock()
	defer ll.mutex.RUnlock()
	return ll.head
}

func (ll *LinkedList) GetTail() *Node {
	ll.mutex.RLock()
	defer ll.mutex.RUnlock()
	return ll.tail
}

func (ll *LinkedList) Prepend(data interface{}) {
	ll.mutex.Lock()
	defer ll.mutex.Unlock()
	newNode := &Node{data: data}
	if ll.head == nil {
		ll.head = newNode
		ll.tail = newNode
	} else {
		newNode.next = ll.head
		ll.head = newNode
	}
	ll.nodeMap[data] = newNode
	ll.length++
}

func (ll *LinkedList) Append(data interface{}) {
	ll.mutex.Lock()
	defer ll.mutex.Unlock()
	newNode := &Node{data: data}
	if ll.head == nil {
		ll.head = newNode
		ll.tail = newNode
	} else {
		ll.tail.next = newNode
		ll.tail = newNode
	}
	ll.nodeMap[data] = newNode
	ll.length++
}

func (ll *LinkedList) InsertBetween(data, before, after interface{}) {
	ll.mutex.Lock()
	defer ll.mutex.Unlock()
	newNode := &Node{data: data}
	curr := ll.head

	for curr != nil && curr.data != after {
		curr = curr.next
	}

	if curr != nil && curr.next != nil && curr.next.data == before {
		newNode.next = curr.next
		curr.next = newNode
		ll.nodeMap[data] = newNode
		ll.length++
	}
}

func (ll *LinkedList) DeleteHead() {
	ll.mutex.Lock()
	defer ll.mutex.Unlock()
	if ll.head != nil {
		delete(ll.nodeMap, ll.head.data)
		ll.head = ll.head.next
		if ll.head == nil {
			ll.tail = nil
		}
		ll.length--
	}
}

func (ll *LinkedList) DeleteTail() {
	ll.mutex.Lock()
	defer ll.mutex.Unlock()
	if ll.head == nil {
		return
	}
	if ll.head.next == nil {
		delete(ll.nodeMap, ll.head.data)
		ll.head = nil
		ll.tail = nil
	} else {
		prevNode := ll.head
		for prevNode.next != nil && prevNode.next.next != nil {
			prevNode = prevNode.next
		}
		delete(ll.nodeMap, prevNode.next.data)
		prevNode.next = nil
		ll.tail = prevNode
	}
	ll.length--
}

func (ll *LinkedList) DeleteAny(target interface{}) {
	ll.mutex.Lock()
	defer ll.mutex.Unlock()
	if ll.head == nil {
		return
	}

	if ll.head.data == target {
		delete(ll.nodeMap, ll.head.data)
		ll.head = ll.head.next
		if ll.head == nil {
			ll.tail = nil
		}
		ll.length--
	} else {
		prevNode := ll.head
		curr := ll.head.next

		for curr != nil && curr.data != target {
			prevNode = curr
			curr = curr.next
		}

		if curr != nil {
			prevNode.next = curr.next
			if curr.next == nil {
				ll.tail = prevNode
			}
			delete(ll.nodeMap, curr.data)
			ll.length--
		}
	}
}

func (ll *LinkedList) Size() int {
	ll.mutex.RLock()
	defer ll.mutex.RUnlock()
	return ll.length
}

func (ll *LinkedList) ReverseList() {
	ll.mutex.Lock()
	defer ll.mutex.Unlock()
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

func (ll *LinkedList) Find(data interface{}) *Node {
	ll.mutex.RLock()
	defer ll.mutex.RUnlock()
	return ll.nodeMap[data]
}

func (ll *LinkedList) Clear() {
	ll.mutex.Lock()
	defer ll.mutex.Unlock()
	ll.head = nil
	ll.tail = nil
	ll.length = 0
	ll.nodeMap = make(map[interface{}]*Node)
}

func (ll *LinkedList) PrintList() {
	ll.mutex.RLock()
	defer ll.mutex.RUnlock()
	curr := ll.head
	for curr != nil {
		fmt.Printf("%v -> ", curr.data)
		curr = curr.next
	}
	fmt.Println("nil")
}

func main() {
	ll := NewLinkedList()

	// Adding data to the list
	ll.Append("Node 1")
	ll.Append("Node 2")
	ll.Append("Node 3")

	// Printing the list
	fmt.Println("List after adding nodes:")
	ll.PrintList()

	// Deleting a node
	ll.DeleteAny("Node 2")

	// Printing the list after deletion
	fmt.Println("List after deleting a node:")
	ll.PrintList()

	// Reversing the list
	ll.ReverseList()

	// Printing the reversed list
	fmt.Println("List after reversing:")
	ll.PrintList()
}
