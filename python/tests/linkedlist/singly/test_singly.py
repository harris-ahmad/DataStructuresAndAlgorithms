from src.linkedlist.singly.list import LinkedList

import pytest

NUM_ELEMENTS = 100_000


@pytest.fixture
def linked_list_append_fixture() -> LinkedList:
    ll = LinkedList()
    
    for i in range(NUM_ELEMENTS):
        ll.append(f"node({i})")
        
    return ll


@pytest.fixture
def linked_list_prepend_fixture() -> LinkedList:
    ll = LinkedList()
    
    for i in range(NUM_ELEMENTS):
        ll.prepend(f"node({i})")
    
    return ll


def test_append(linked_list_append_fixture):
    ll = linked_list_append_fixture
    
    assert len(ll) == NUM_ELEMENTS
    assert ll.get_tail().data == f"node({NUM_ELEMENTS-1})"
    assert ll.get_head().data == "node(0)"
    

def test_prepend(linked_list_prepend_fixture):
    ll = linked_list_prepend_fixture
    
    assert len(ll) == NUM_ELEMENTS
    assert ll.get_tail().data == f"node({NUM_ELEMENTS-1})"
    assert ll.get_head().data == f"node({NUM_ELEMENTS-99999})"