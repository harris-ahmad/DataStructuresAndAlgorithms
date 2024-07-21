#include <stdio.h>
#include <stdlib.h>

#define HASHMAP_SIZE 1024

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

typedef struct LinkedList {
  Node *head;
} LinkedList;

/* HashMap Implementation*/
typedef struct HashMapEntry {
  int key;
  Node *value;
  struct HashMapEntry *next;
} HashMapEntry;

typedef struct HashMap {
  HashMapEntry **table;
} HashMap;

unsigned int hash(int key) { return key % HASHMAP_SIZE; }

HashMap *createHashMap() {
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  map->table = (HashMapEntry **)malloc(HASHMAP_SIZE * sizeof(HashMapEntry));
  for (int i = 0; i < HASHMAP_SIZE; i++) {
    map->table[i] = NULL;
  }
  return map;
}

HashMapEntry *createHashMapEntry(int key, Node *value) {
  HashMapEntry *entry = (HashMapEntry *)malloc(sizeof(HashMapEntry));
  entry->key = key;
  entry->value = value;
  entry->next = NULL;
  return entry;
}

void hashMapInsert(HashMap *map, int key, Node *value) {
  unsigned int index = hash(key);
  HashMapEntry *newEntry = createHashMapEntry(key, value);
  newEntry->next = map->table[index];
  map->table[index] = newEntry;
}

Node *hashMapFind(HashMap *map, int key) {
  unsigned index = hash(key);
  HashMapEntry *entry = map->table[index];
  HashMapEntry *prev = NULL;
  while (entry) {
    if (entry->key == key) {
      return entry->value;
    }
    entry = entry->next;
  }
  return NULL;
}

void hashMapRemove(HashMap *map, int key) {
  unsigned index = hash(key);
  HashMapEntry *entry = map->table[index];
  HashMapEntry *prev = NULL;
  while (entry) {
    if (entry->key == key) {
      if (prev) {
        prev->next = entry->next;
      } else {
        map->table[index] = entry->next;
      }
      free(entry);
      return;
    }
    prev = entry;
    entry = entry->next;
  }
}

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