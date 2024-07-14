
# LinkedList Concepts - Singly Linked List

## Introduction

A **singly linked list** is a linear data structure where each element is a separate object, called a node. Each node contains two items: data and a reference (or link) to the next node in the sequence.

## Node Structure

A node in a singly linked list contains:

- `data`: The value stored in the node.

- `next`: A reference to the next node in the list.

### LinkedList Operations

#### 1. Prepend

**Description:** Adds a node to the beginning of the list.

**Algorithm:**

1. Create a new node with the given data.
2. If the list is empty, set both `head` and `tail` to the new node.
3. Otherwise, set the new node's `next` to the current `head` and update the `head` to the new node.
4. Update the node map (if using one) and increment the length of the list.

**Diagram:**

```text

Before:   null
After:    Head -> [data] -> null

```

```text

Before:   Head -> [1] -> [2] -> [3] -> null
Prepend:  Head -> [0] -> [1] -> [2] -> [3] -> null

```

#### 2. Append

**Description:** Adds a node to the end of the list.

**Algorithm:**

1. Create a new node with the given data.
2. If the list is empty, set both `head` and `tail` to the new node.
3. Otherwise, set the current `tail`'s `next` to the new node and update the `tail`.
4. Update the node map (if using one) and increment the length of the list.

**Diagram:**

```text
Before:   Head -> [1] -> [2] -> [3] -> null
Append:   Head -> [1] -> [2] -> [3] -> [4] -> null
```

#### 3. Insert Between

**Description:** Inserts a node between two specified nodes.

**Algorithm:**

1. Create a new node with the given data.
2. Traverse the list to find the node with data matching `after`.
3. If found and the next node's data matches `before`, insert the new node between them by updating the `next` references.
4. Update the node map (if using one) and increment the length of the list.

**Diagram:**

```text
Before:   Head -> [1] -> [3] -> [4] -> null
Insert:   Head -> [1] -> [2] -> [3] -> [4] -> null
```

#### 4. Delete Head

**Description:** Removes the head node.

**Algorithm:**

1. If the list is not empty, update the `head` to the next node.
2. Update the node map (if using one) and decrement the length of the list.
3. If the new `head` is null, also set `tail` to null.

**Diagram:**

```text
Before:   Head -> [1] -> [2] -> [3] -> null
Delete:   Head -> [2] -> [3] -> null
```

#### 5. Delete Tail

**Description:** Removes the tail node.

**Algorithm:**

1. If the list is empty, do nothing.
2. If there's only one node, update `head` and `tail` to null.
3. Otherwise, traverse the list to find the second-to-last node.
4. Set its `next` to null and update the `tail`.
5. Update the node map (if using one) and decrement the length of the list.

**Diagram:**

```text
Before:   Head -> [1] -> [2] -> [3] -> null
Delete:   Head -> [1] -> [2] -> null
```

#### 6. Delete Any

**Description:** Removes a node with a specified target data.

**Algorithm:**

1. If the list is empty, do nothing.
2. If the head node matches the target, update `head` to the next node.
3. Otherwise, traverse the list to find the node with the target data.
4. If found, remove it by updating the previous node's `next` reference.
5. Update the node map (if using one) and decrement the length of the list.
6. If the removed node was the `tail`, update the `tail` reference.

**Diagram:**

```text
Before:   Head -> [1] -> [2] -> [3] -> null
Delete:   Head -> [1] -> [3] -> null
```

#### 7. Reverse List

**Description:** Reverses the linked list in place.

**Algorithm:**

1. Initialize `prev` to null, `curr` to `head`, and `next` to null.
2. Iterate through the list, reversing the `next` pointers of each node.
3. Update the `head` to the last node processed.
4. Update the `tail` to the old `head`.

**Diagram:**

```text
Before:   Head -> [1] -> [2] -> [3] -> null
Reverse:  Head -> [3] -> [2] -> [1] -> null
```

#### 8. Find

**Description:** Finds a node by its ID.

**Algorithm:**

1. Use the node map to look up the node by its ID.
2. Return the node if found, otherwise return null.

**Diagram:**

```text
Nodes:    Head -> [1] -> [2] -> [3] -> null
Find:     [2] (Returns node with data 2)
```

#### 9. Clear

**Description:** Clears the list, removing all nodes.

**Algorithm:**

1. Set `head` and `tail` to null.
2. Reset the length to 0.
3. Clear the node map (if using one).

**Diagram:**

```text
Before:   Head -> [1] -> [2] -> [3] -> null
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
Nodes:    Head -> [1] -> [2] -> [3] -> null
Print:    "1 -> 2 -> 3"
```
