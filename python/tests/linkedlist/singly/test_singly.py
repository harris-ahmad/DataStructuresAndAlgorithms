from src.linkedlist.singly.list import LinkedList

import time
import pytest

@pytest.fixture
def linked_list_fixture() -> LinkedList:
    ll = LinkedList()
    num_elements = 100_000
    
    start_time = time.perf_counter()
    for i in range(num_elements):
        ll.append(f"node({i})")
    end_time = time.perf_counter()
    
    duration = end_time - start_time
        
    return ll, duration, num_elements

def test_append(linked_list_fixture):
    ll, _, num_elements = linked_list_fixture
    
    assert len(ll) == num_elements
    assert ll.get_tail().data == f"node({num_elements-1})"
    assert ll.get_head().data == "node(0)"