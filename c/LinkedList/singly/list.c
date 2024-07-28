#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  void *data;
  struct Node *next;
  int ref_count;
} Node;

typedef struct LinkedList {
  Node *head;
} LinkedList;

// functions for garbage collection
void incrementRefCount(Node *node) {
  if (node) {
    node->ref_count++;
  }
}

void decrementRefCount(Node *node) {
  if (node) {
    node->ref_count--;
    if (node->ref_count <= 0) {
      free(node);
    }
  }
}

Node *createNode(void *data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;
  newNode->ref_count = 1;
  return newNode;
}

LinkedList *createLinkedList() {
  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  list->head = NULL;
  return list;
}

Node *getHead(LinkedList *list) { return list->head; }

Node *getTail(LinkedList *list) {
  if (!list->head)
    return (Node *)NULL;
  else {
    Node *lastNode = list->head;
    while (lastNode && lastNode->next) {
      lastNode = lastNode->next;
    }
    return lastNode;
  }
}

void prepend(LinkedList *list, void *data) {
  Node *newNode = createNode(data);
  newNode->next = list->head;
  list->head = newNode;
}

void append(LinkedList *list, void *data) {
  Node *newNode = createNode(data);
  if (!list->head) {
    list->head = newNode;
  } else {
    Node *lastNode = getTail(list);
    lastNode->next = newNode;
  }
}

void insertBetween(LinkedList *list, void *data, void *after) {
  Node *newNode = createNode(data);
  Node *prevNode = list->head;

  while (prevNode && prevNode->data != after) {
    prevNode = prevNode->next;
  }

  if (prevNode) {
    newNode->next = prevNode->next;
    prevNode->next = newNode;
  }
}

// Function to delete the head node
void deleteHead(LinkedList *list) {
  if (list->head) {
    Node *temp = list->head;
    list->head = list->head->next;
    decrementRefCount(temp);
  }
}

// Function to delete the tail node
void deleteTail(LinkedList *list) {
  if (!list->head) {
    return;
  }
  if (!list->head->next) {
    decrementRefCount(list->head);
    list->head = NULL;
  } else {
    Node *prevNode = list->head;
    while (prevNode->next && prevNode->next->next) {
      prevNode = prevNode->next;
    }
    decrementRefCount(prevNode->next);
    prevNode->next = NULL;
  }
}

// Function to delete any node with a specific value
void deleteAny(LinkedList *list, void *target) {
  if (!list->head) {
    return;
  }

  if (list->head->data == target) {
    Node *temp = list->head;
    list->head = list->head->next;
    decrementRefCount(temp);
  } else {
    Node *prevNode = list->head;
    Node *curr = list->head->next;

    while (curr && curr->data != target) {
      prevNode = curr;
      curr = curr->next;
    }

    if (curr) {
      prevNode->next = curr->next;
      decrementRefCount(curr);
    }
  }
}