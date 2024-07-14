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
