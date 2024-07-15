import unittest
from list import LinkedList


class TestLinkedList(unittest.TestCase):

    class TestData:
        def __init__(self, id, value):
            self.id = id
            self.value = value

        def __str__(self):
            return f"({self.id}: {self.value})"

    def setUp(self):
        self.linked_list = LinkedList()

    def test_prepend(self):
        data1 = self.TestData(1, "data1")
        data2 = self.TestData(2, "data2")
        self.linked_list.prepend(data1)
        self.linked_list.prepend(data2)
        self.assertEqual(self.linked_list.get_head().data, data2)
        self.assertEqual(self.linked_list.get_tail().data, data1)
        self.assertEqual(self.linked_list.size(), 2)

    def test_append(self):
        data1 = self.TestData(1, "data1")
        data2 = self.TestData(2, "data2")
        self.linked_list.append(data1)
        self.linked_list.append(data2)
        self.assertEqual(self.linked_list.get_head().data, data1)
        self.assertEqual(self.linked_list.get_tail().data, data2)
        self.assertEqual(self.linked_list.size(), 2)

    def test_insert_between(self):
        data1 = self.TestData(1, "data1")
        data2 = self.TestData(2, "data2")
        data3 = self.TestData(3, "data3")
        self.linked_list.append(data1)
        self.linked_list.append(data3)
        self.linked_list.insert_between(data2, before=data3, after=data1)
        self.assertEqual(self.linked_list.size(), 3)
        self.assertEqual(self.linked_list.get_head().next.data, data2)
        self.assertEqual(self.linked_list.get_head().next.next.data, data3)

    def test_delete_head(self):
        data1 = self.TestData(1, "data1")
        data2 = self.TestData(2, "data2")
        self.linked_list.append(data1)
        self.linked_list.append(data2)
        self.linked_list.delete_head()
        self.assertEqual(self.linked_list.get_head().data, data2)
        self.assertEqual(self.linked_list.size(), 1)
        self.linked_list.delete_head()
        self.assertIsNone(self.linked_list.get_head())
        self.assertIsNone(self.linked_list.get_tail())
        self.assertEqual(self.linked_list.size(), 0)

    def test_delete_tail(self):
        data1 = self.TestData(1, "data1")
        data2 = self.TestData(2, "data2")
        self.linked_list.append(data1)
        self.linked_list.append(data2)
        self.linked_list.delete_tail()
        self.assertEqual(self.linked_list.get_tail().data, data1)
        self.assertEqual(self.linked_list.size(), 1)
        self.linked_list.delete_tail()
        self.assertIsNone(self.linked_list.get_tail())
        self.assertIsNone(self.linked_list.get_head())
        self.assertEqual(self.linked_list.size(), 0)

    def test_delete_any(self):
        data1 = self.TestData(1, "data1")
        data2 = self.TestData(2, "data2")
        data3 = self.TestData(3, "data3")
        self.linked_list.append(data1)
        self.linked_list.append(data2)
        self.linked_list.append(data3)
        self.linked_list.delete_any(data2)
        self.assertEqual(self.linked_list.size(), 2)
        self.assertEqual(self.linked_list.get_head().next.data, data3)
        self.linked_list.delete_any(data1)
        self.assertEqual(self.linked_list.size(), 1)
        self.assertEqual(self.linked_list.get_head().data, data3)
        self.linked_list.delete_any(data3)
        self.assertEqual(self.linked_list.size(), 0)
        self.assertIsNone(self.linked_list.get_head())
        self.assertIsNone(self.linked_list.get_tail())

    def test_reverse_list(self):
        data1 = self.TestData(1, "data1")
        data2 = self.TestData(2, "data2")
        data3 = self.TestData(3, "data3")
        self.linked_list.append(data1)
        self.linked_list.append(data2)
        self.linked_list.append(data3)
        self.linked_list.reverse_list()
        self.assertEqual(self.linked_list.get_head().data, data3)
        self.assertEqual(self.linked_list.get_head().next.data, data2)
        self.assertEqual(self.linked_list.get_head().next.next.data, data1)
        self.assertEqual(self.linked_list.get_tail().data, data1)

    def test_find(self):
        data1 = self.TestData(1, "data1")
        data2 = self.TestData(2, "data2")
        self.linked_list.append(data1)
        self.linked_list.append(data2)
        self.assertEqual(self.linked_list.find(1), self.linked_list.get_head())
        self.assertEqual(self.linked_list.find(2), self.linked_list.get_tail())
        self.assertIsNone(self.linked_list.find(3))

    def test_clear(self):
        data1 = self.TestData(1, "data1")
        data2 = self.TestData(2, "data2")
        self.linked_list.append(data1)
        self.linked_list.append(data2)
        self.linked_list.clear()
        self.assertIsNone(self.linked_list.get_head())
        self.assertIsNone(self.linked_list.get_tail())
        self.assertEqual(self.linked_list.size(), 0)
        self.assertEqual(self.linked_list.node_map, {})


if __name__ == "__main__":
    unittest.main()
