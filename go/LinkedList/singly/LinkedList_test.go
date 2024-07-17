package singly

import (
	"testing"
)

func TestAppend(t *testing.T) {
	ll := NewLinkedList()
	ll.Append(1, "Node 1")
	ll.Append(2, "Node 2")
	ll.Append(3, "Node 3")

	if ll.Size() != 3 {
		t.Errorf("Expected size 3, got %d", ll.Size())
	}

	if ll.Find(1).data != "Node 1" || ll.Find(2).data != "Node 2" || ll.Find(3).data != "Node 3" {
		t.Errorf("Data mismatch")
	}
}

func TestPrepend(t *testing.T) {
	ll := NewLinkedList()
	ll.Prepend(1, "Node 1")
	ll.Prepend(2, "Node 2")
	ll.Prepend(3, "Node 3")

	if ll.Size() != 3 {
		t.Errorf("Expected size 3, got %d", ll.Size())
	}

	if ll.head.data != "Node 3" {
		t.Errorf("Expected head data 'Node 3', got '%v'", ll.head.data)
	}
	if ll.tail.data != "Node 1" {
		t.Errorf("Expected tail data 'Node 1', got '%v'", ll.tail.data)
	}
}

func TestDeleteHead(t *testing.T) {
	ll := NewLinkedList()
	ll.Append(1, "Node 1")
	ll.Append(2, "Node 2")
	ll.Append(3, "Node 3")

	ll.DeleteHead()
	if ll.Size() != 2 {
		t.Errorf("Expected size 2, got %d", ll.Size())
	}
	if ll.head.data != "Node 2" {
		t.Errorf("Expected head data 'Node 2', got '%v'", ll.head.data)
	}
}

func TestDeleteTail(t *testing.T) {
	ll := NewLinkedList()
	ll.Append(1, "Node 1")
	ll.Append(2, "Node 2")
	ll.Append(3, "Node 3")

	ll.DeleteTail()
	if ll.Size() != 2 {
		t.Errorf("Expected size 2, got %d", ll.Size())
	}
	if ll.tail.data != "Node 2" {
		t.Errorf("Expected tail data 'Node 2', got '%v'", ll.tail.data)
	}
}

func TestDeleteAny(t *testing.T) {
	ll := NewLinkedList()
	ll.Append(1, "Node 1")
	ll.Append(2, "Node 2")
	ll.Append(3, "Node 3")

	ll.DeleteAny(2)
	if ll.Size() != 2 {
		t.Errorf("Expected size 2, got %d", ll.Size())
	}
	if ll.Find(2) != nil {
		t.Errorf("Expected nil, got %v", ll.Find(2))
	}
	if ll.head.next.data != "Node 3" {
		t.Errorf("Expected next node to be 'Node 3', got '%v'", ll.head.next.data)
	}
}

func TestInsertBetween(t *testing.T) {
	ll := NewLinkedList()
	ll.Append(1, "Node 1")
	ll.Append(3, "Node 3")
	ll.InsertBetween(2, "Node 2", "Node 3", "Node 1")

	if ll.Size() != 3 {
		t.Errorf("Expected size 3, got %d", ll.Size())
	}
	if ll.head.next.data != "Node 2" {
		t.Errorf("Expected next node to be 'Node 2', got '%v'", ll.head.next.data)
	}
	if ll.head.next.next.data != "Node 3" {
		t.Errorf("Expected next next node to be 'Node 3', got '%v'", ll.head.next.next.data)
	}
}

func TestReverseList(t *testing.T) {
	ll := NewLinkedList()
	ll.Append(1, "Node 1")
	ll.Append(2, "Node 2")
	ll.Append(3, "Node 3")

	ll.ReverseList()

	if ll.head.data != "Node 3" {
		t.Errorf("Expected head data 'Node 3', got '%v'", ll.head.data)
	}
	if ll.head.next.data != "Node 2" {
		t.Errorf("Expected next node to be 'Node 2', got '%v'", ll.head.next.data)
	}
	if ll.head.next.next.data != "Node 1" {
		t.Errorf("Expected next next node to be 'Node 1', got '%v'", ll.head.next.next.data)
	}
}

func TestClear(t *testing.T) {
	ll := NewLinkedList()
	ll.Append(1, "Node 1")
	ll.Append(2, "Node 2")
	ll.Append(3, "Node 3")

	ll.Clear()
	if ll.Size() != 0 {
		t.Errorf("Expected size 0, got %d", ll.Size())
	}
	if ll.head != nil || ll.tail != nil {
		t.Errorf("Expected head and tail to be nil")
	}
}

func TestFind(t *testing.T) {
	ll := NewLinkedList()
	ll.Append(1, "Node 1")
	ll.Append(2, "Node 2")

	node := ll.Find(1)
	if node == nil {
		t.Errorf("Expected node with id 1, got nil")
	}
	if node.data != "Node 1" {
		t.Errorf("Expected node data 'Node 1', got '%v'", node.data)
	}
}

func TestSize(t *testing.T) {
	ll := NewLinkedList()
	ll.Append(1, "Node 1")
	ll.Append(2, "Node 2")

	if ll.Size() != 2 {
		t.Errorf("Expected size 2, got %d", ll.Size())
	}
}
