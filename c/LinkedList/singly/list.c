#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

typedef struct LinkedList {
  Node *head;
} LinkedList;

Node *createNode(void *data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

Node *getHead(LinkedList *list) { return list->head; }

Node *getTail(LinkedList *list) {
  Node *lastNode = list->head;
  while (lastNode && lastNode->next) {
    lastNode = lastNode->next;
  }
  return lastNode;
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

void deleteHead(LinkedList *list) {
  if (list->head)
    list->head = list->head->next;
}

void deleteTail(LinkedList *list) {
  if (!list->head) {
    return;
  }
  if (!list->head->next) {
    list->head = NULL;
  } else {
    Node *prevNode = list->head;
    while (prevNode->next && prevNode->next->next) {
      prevNode = prevNode->next;
    }
    prevNode->next = NULL;
  }
}

void deleteAny(LinkedList *list, void *data) {
  if (!list->head)
    return;

  if (list->head->data == data) {
    list->head = list->head->next;
  } else {
    Node *prevNode = list->head;
    Node *curr = list->head->next;

    while (curr && curr->data != data) {
      prevNode = curr;
      curr = curr->next;
    }

    if (curr) {
      prevNode->next = curr->next;
    }
  }
}

int size(LinkedList *list) {
  int count = 0;
  Node *curr = list->head;
  while (curr) {
    count++;
    curr = curr->next;
  }
  return count;
}

void reverseList(LinkedList *list) {
  Node *curr = list->head;
  Node *prev = NULL;
  while (curr) {
    Node *next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  list->head = prev;
}

Node *find(LinkedList *list, void *data) {
  Node *curr = list->head;
  while (curr) {
    if (curr->data == data) {
      return curr;
    }
    curr = curr->next;
  }
  return (Node *)NULL;
}

void clear(LinkedList *list) { list->head = NULL; }