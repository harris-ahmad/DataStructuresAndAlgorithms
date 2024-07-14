package singly

type Node struct {
	data interface{}
	next *Node
}

type LinkedList struct {
	head    *Node
	tail    *Node
	length  int
	nodeMap map[int]*Node
}

func NewLinkedList() *LinkedList {
	return &LinkedList{
		head:    nil,
		tail:    nil,
		length:  0,
		nodeMap: make(map[int]*Node),
	}
}
