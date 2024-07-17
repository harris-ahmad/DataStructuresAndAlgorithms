# LinkedList Concepts - Doubly Linked List

## Introduction

A **doubly linked list** is a linear data structure where each element is a separate object, called a node. Each node contains three items: data, a reference (or link) to the next node in the sequence, and a reference to the previous node.

## Node Structure

A node in a doubly linked list contains:

- `data`: The value stored in the node.
- `next`: A reference to the next node in the list.
- `prev`: A reference to the previous node in the list.

### LinkedList Operations

#### 1. Prepend

**Description:** Adds a node to the beginning of the list.

**Algorithm:**

1. Create a new node with the given data.
2. If the list is empty, set both `head` and `tail` to the new node.
3. Otherwise, set the new node's `next` to the current `head`, and the current `head`'s `prev` to the new node.
4. Update the `head` to the new node.
5. Update the node map (if using one) and increment the length of the list.

**Diagram:**

```text

Before:   null
After:    Head -> [data] <-> null

```

```text

Before:   Head -> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> null
Prepend:  Head -> [(0, "d")] <-> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> null

```

#### 2. Append

**Description:** Adds a node to the end of the list.

**Algorithm:**

1. Create a new node with the given data.
2. If the list is empty, set both `head` and `tail` to the new node.
3. Otherwise, set the current `tail`'s `next` to the new node, and the new node's `prev` to the current `tail`.
4. Update the `tail` to the new node.
5. Update the node map (if using one) and increment the length of the list.

**Diagram:**

```text
Before:   Head -> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> null
Append:   Head -> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> [(4, "d")] <-> null
```

#### 3. Insert Between

**Description:** Inserts a node between two specified nodes.

**Algorithm:**

1. Create a new node with the given data.
2. Traverse the list to find the node with data matching `after`.
3. If found and the next node's data matches `before`, insert the new node between them by updating the `next` and `prev` references.
4. Update the node map (if using one) and increment the length of the list.

**Diagram:**

```text
Before:   Head -> [(1, "a")] <->  [(3, "c")] <-> [(4, "d")] <-> null
Insert:   Head -> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> [(4, "d")] <-> null
```

#### 4. Delete Head

**Description:** Removes the head node.

**Algorithm:**

1. If the list is not empty, update the `head` to the next node.
2. Update the `prev` of the new `head` to null (if it exists).
3. Update the node map (if using one) and decrement the length of the list.
4. If the new `head` is null, also set `tail` to null.

**Diagram:**

```text
Before:   Head -> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> null
Delete:   Head -> [(2, "b")] <-> [(3, "c")] <-> [(4, "d")] <-> null
```

#### 5. Delete Tail

**Description:** Removes the tail node.

**Algorithm:**

1. If the list is empty, do nothing.
2. If there's only one node, update `head` and `tail` to null.
3. Otherwise, update the `tail` to the previous node and set its `next` to null.
4. Update the node map (if using one) and decrement the length of the list.

**Diagram:**

```text
Before:   Head -> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> [(4, "d")] <-> null
Delete:   Head -> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> null
```

#### 6. Delete Any

**Description:** Removes a node with a specified target data.

**Algorithm:**

1. If the list is empty, do nothing.
2. If the head node matches the target, delete the head node.
3. If the tail node matches the target, delete the tail node.
4. Otherwise, traverse the list to find the node with the target data.
5. If found, remove it by updating the `next` and `prev` references of the adjacent nodes.
6. Update the node map (if using one) and decrement the length of the list.

**Diagram:**

```text
Before:   Head -> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> [(4, "d")] <-> null
Delete(2)
Delete:   Head -> [(1, "a")] <-> [(3, "c")] <-> [(4, "d")] <-> null
```

#### 7. Reverse List

**Description:** Reverses the linked list in place.

**Algorithm:**

1. Initialize `prev` to null, `curr` to `head`, and `next` to null.
2. Iterate through the list, reversing the `next` and `prev` pointers of each node.
3. Update the `head` to the last node processed.
4. Update the `tail` to the old `head`.

**Diagram:**

```text
Before:   Head -> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> null
Reverse:  Head -> [(3, "c")] <-> [(2, "b")] <-> [(1, "a")]  <-> null
```

#### 8. Find

**Description:** Finds a node by its ID.

**Algorithm:**

1. Use the node map to look up the node by its ID.
2. Return the node if found, otherwise return null.

**Diagram:**

```text
Nodes:    Head -> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> [(4, "d")] <-> null
Find:     [(2, "b")] (Returns node with data (2, "b"))
```

#### 9. Clear

**Description:** Clears the list, removing all nodes.

**Algorithm:**

1. Set `head` and `tail` to null.
2. Reset the length to 0.
3. Clear the node map (if using one).

**Diagram:**

```text
Before:   Head -> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> [(4, "d")] <-> null
Clear:    null
```

#### 10. Print

**Description:** Prints the list data in a readable format.

**Algorithm:**

1. Initialize an empty array.
2. Traverse the list, adding each node's data to the array.
3. Join and print the array as a string.

**Diagram:**

```text
Nodes:    Head -> [(1, "a")] <-> [(2, "b")] <-> [(3, "c")] <-> [(4, "d")] <-> null
Print:    "(1, "a") <-> (2, "b") <-> (3, "c") <-> (4, "d")"
```
