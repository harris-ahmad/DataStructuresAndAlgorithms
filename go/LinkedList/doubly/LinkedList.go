package singly

type Node struct {
	data interface{}
	next *Node
	prev *Node
}

type LinkedList struct {
	head   *Node
	tail   *Node
	length int
}

func NewNode(data interface{}) *Node {
	return &Node{data: data}
}

func NewLinkedList() *LinkedList {
	return &LinkedList{
		head:   nil,
		tail:   nil,
		length: 0,
	}
}

func (dll *LinkedList) Prepend(data interface{}) {
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

func (dll *LinkedList) Append(data interface{}) {
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

func (dll *LinkedList) InsertBetween(data interface{}, after interface{}) {
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
