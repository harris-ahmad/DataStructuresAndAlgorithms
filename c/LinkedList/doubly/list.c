#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
    struct Node *prev;
    int ref_count;
} Node;

typedef struct DoublyLinkedList {
    Node *head;
    Node *tail;
} DoublyLinkedList;

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
    newNode->prev = NULL;
    newNode->ref_count = 1;
    return newNode;
}

DoublyLinkedList *createDoublyLinkedList() {
    DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

Node *getHead(DoublyLinkedList *list) {
    return list->head;
}

Node *getTail(DoublyLinkedList *list) {
    return list->tail;
}

void prepend(DoublyLinkedList *list, void *data) {
    Node *newNode = createNode(data);
    if (!list->head) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void append(DoublyLinkedList *list, void *data) {
    Node *newNode = createNode(data);
    if (!list->head) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void insertBetween(DoublyLinkedList *list, void *data, void *after) {
    Node *newNode = createNode(data);
    Node *curr = list->head;

    while (curr && curr->data != after) {
        curr = curr->next;
    }

    if (curr) {
        newNode->next = curr->next;
        newNode->prev = curr;
        if (curr->next) {
            curr->next->prev = newNode;
        } else {
            list->tail = newNode;
        }
        curr->next = newNode;
    }
}

void deleteHead(DoublyLinkedList *list) {
    if (list->head) {
        Node *temp = list->head;
        list->head = list->head->next;
        if (list->head) {
            list->head->prev = NULL;
        } else {
            list->tail = NULL;
        }
        decrementRefCount(temp);
    }
}

void deleteTail(DoublyLinkedList *list) {
    if (!list->tail) {
        return;
    }
    if (list->tail == list->head) {
        decrementRefCount(list->tail);
        list->head = NULL;
        list->tail = NULL;
    } else {
        Node *temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        decrementRefCount(temp);
    }
}

void deleteAny(DoublyLinkedList *list, void *target) {
    Node *curr = list->head;

    while (curr && curr->data != target) {
        curr = curr->next;
    }

    if (curr) {
        if (curr->prev) {
            curr->prev->next = curr->next;
        } else {
            list->head = curr->next;
        }

        if (curr->next) {
            curr->next->prev = curr->prev;
        } else {
            list->tail = curr->prev;
        }

        decrementRefCount(curr);
    }
}

int size(DoublyLinkedList *list) {
    int count = 0;
    Node *curr = list->head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    return count;
}

void reverseList(DoublyLinkedList *list) {
    Node *curr = list->head;
    Node *temp = NULL;

    while (curr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }

    if (temp) {
        list->head = temp->prev;
    }
}

Node *find(DoublyLinkedList *list, void *data) {
    Node *curr = list->head;
    while (curr) {
        if (curr->data == data) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void clear(DoublyLinkedList *list) {
    Node *curr = list->head;
    Node *next;
    while (curr) {
        next = curr->next;
        decrementRefCount(curr);
        curr = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

void printListForward(DoublyLinkedList *list) {
    Node *curr = list->head;
    while (curr) {
        printf("%p ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void printListBackward(DoublyLinkedList *list) {
    Node *curr = list->tail;
    while (curr) {
        printf("%p ", curr->data);
        curr = curr->prev;
    }
    printf("\n");
}

int main() {
    DoublyLinkedList *list = createDoublyLinkedList();

    int a = 1, b = 2, c = 3, d = 4;
    append(list, &a);
    append(list, &b);
    prepend(list, &c);
    insertBetween(list, &d, &a);

    printf("List printed forward: ");
    printListForward(list);

    printf("List printed backward: ");
    printListBackward(list);

    deleteHead(list);
    printf("List after deleting head: ");
    printListForward(list);

    deleteTail(list);
    printf("List after deleting tail: ");
    printListForward(list);

    deleteAny(list, &b);
    printf("List after deleting element b: ");
    printListForward(list);

    printf("List size: %d\n", size(list));

    reverseList(list);
    printf("List after reversing: ");
    printListForward(list);

    clear(list);
    printf("List after clearing: ");
    printListForward(list);

    free(list);

    return 0;
}
