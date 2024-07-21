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

Node *getHead(LinkedList *list) {
  return list->head;
}

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

