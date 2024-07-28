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
void incrementReference(Node *node) {
	if (node) {
		node->ref_count++;
	}
}

void decrementReference(Node *node) {
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

