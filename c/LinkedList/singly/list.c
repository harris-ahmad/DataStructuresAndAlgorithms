#include <stdio.h>
#include <stdlib.h>

#define HASHMAP_SIZE 1024 // Define the size of the hashmap

typedef struct Node {
  void *data;
  int ref_count; // Reference count for garbage collection
  struct Node *next;
} Node;

typedef struct HashMapEntry {
  int key;
  Node *value;
  struct HashMapEntry *next;
} HashMapEntry;

typedef struct HashMap {
  HashMapEntry **table;
} HashMap;

typedef struct LinkedList {
  Node *head;
  HashMap *node_map;
} LinkedList;

unsigned int hash(int key) { return key % HASHMAP_SIZE; }

// Function to create a new hashmap
HashMap *createHashMap() {
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  map->table = (HashMapEntry **)malloc(HASHMAP_SIZE * sizeof(HashMapEntry *));
  for (int i = 0; i < HASHMAP_SIZE; i++) {
    map->table[i] = NULL;
  }
  return map;
}

// Function to create a new hashmap entry
HashMapEntry *createHashMapEntry(int key, Node *value) {
  HashMapEntry *entry = (HashMapEntry *)malloc(sizeof(HashMapEntry));
  entry->key = key;
  entry->value = value;
  entry->next = NULL;
  return entry;
}

// Function to insert an entry into the hashmap
void hashMapInsert(HashMap *map, int key, Node *value) {
  unsigned int index = hash(key);
  HashMapEntry *newEntry = createHashMapEntry(key, value);
  newEntry->next = map->table[index];
  map->table[index] = newEntry;
}

// Function to find an entry in the hashmap
Node *hashMapFind(HashMap *map, int key) {
  unsigned int index = hash(key);
  HashMapEntry *entry = map->table[index];
  while (entry) {
    if (entry->key == key) {
      return entry->value;
    }
    entry = entry->next;
  }
  return NULL;
}

// Function to remove an entry from the hashmap
void hashMapRemove(HashMap *map, int key) {
  unsigned int index = hash(key);
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

// Function to create a new node
Node *createNode(void *data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->ref_count = 1; // Initialize reference count to 1
  newNode->next = NULL;
  return newNode;
}

// Function to increment the reference count
void incrementRefCount(Node *node) {
  if (node) {
    node->ref_count++;
  }
}

// Function to decrement the reference count and free memory if needed
void decrementRefCount(Node *node) {
  if (node) {
    node->ref_count--;
    if (node->ref_count <= 0) {
      free(node);
    }
  }
}

// Function to create a new linked list
LinkedList *createLinkedList() {
  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  list->head = NULL;
  list->node_map = createHashMap();
  return list;
}

// Function to get the head of the list
Node *getHead(LinkedList *list) { return list->head; }

// Function to get the tail of the list
Node *getTail(LinkedList *list) {
  Node *lastNode = list->head;
  while (lastNode && lastNode->next) {
    lastNode = lastNode->next;
  }
  return lastNode;
}

// Function to prepend a node to the list
void prepend(LinkedList *list, void *data, int key) {
  Node *newNode = createNode(data);
  hashMapInsert(list->node_map, key, newNode);
  newNode->next = list->head;
  list->head = newNode;
}

// Function to append a node to the list
void append(LinkedList *list, void *data, int key) {
  Node *newNode = createNode(data);
  hashMapInsert(list->node_map, key, newNode);
  if (!list->head) {
    list->head = newNode;
  } else {
    Node *lastNode = getTail(list);
    lastNode->next = newNode;
  }
}

// Function to insert a node between two nodes
void insertBetween(LinkedList *list, void *data, int key, int after) {
  Node *newNode = createNode(data);
  Node *prevNode = hashMapFind(list->node_map, after);

  if (prevNode) {
    hashMapInsert(list->node_map, key, newNode);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
  }
}

// Function to delete the head node
void deleteHead(LinkedList *list) {
  if (list->head) {
    Node *temp = list->head;
    list->head = list->head->next;
    hashMapRemove(list->node_map, (int)(long)temp->data); // Cast data to int
    decrementRefCount(temp);
  }
}

// Function to delete the tail node
void deleteTail(LinkedList *list) {
  if (!list->head) {
    return;
  }
  if (!list->head->next) {
    hashMapRemove(list->node_map,
                  (int)(long)list->head->data); // Cast data to int
    decrementRefCount(list->head);
    list->head = NULL;
  } else {
    Node *prevNode = list->head;
    while (prevNode->next && prevNode->next->next) {
      prevNode = prevNode->next;
    }
    hashMapRemove(list->node_map,
                  (int)(long)prevNode->next->data); // Cast data to int
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
    hashMapRemove(list->node_map, (int)(long)temp->data); // Cast data to int
    decrementRefCount(temp);
  } else {
    Node *prevNode = list->head;
    Node *curr = list->head->next;

    while (curr && curr->data != target) {
      prevNode = curr;
      curr = curr->next;
    }

    if (curr) {
      hashMapRemove(list->node_map, (int)(long)curr->data); // Cast data to int
      prevNode->next = curr->next;
      decrementRefCount(curr);
    }
  }
}

// Function to get the size of the list
int size(LinkedList *list) {
  int count = 0;
  Node *curr = list->head;
  while (curr) {
    count++;
    curr = curr->next;
  }
  return count;
}

// Function to reverse the list
void reverseList(LinkedList *list) {
  Node *prev = NULL;
  Node *curr = list->head;
  Node *next = NULL;
  while (curr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  list->head = prev;
}

// Function to find a node with a specific value
Node *find(LinkedList *list, int key) {
  return hashMapFind(list->node_map, key);
}

// Function to clear the list
void clear(LinkedList *list) {
  Node *curr = list->head;
  Node *next;
  while (curr) {
    next = curr->next;
    hashMapRemove(list->node_map, (int)(long)curr->data); // Cast data to int
    decrementRefCount(curr);
    curr = next;
  }
  list->head = NULL;
}

// Function to print the list
void printList(LinkedList *list) {
  Node *curr = list->head;
  while (curr) {
    printf("%p ", curr->data);
    curr = curr->next;
  }
  printf("\n");
}

// Function to read data into the list
void readList(LinkedList *list) {
  void *data;
  int key;
  scanf("%d %p", &key, &data);
  append(list, data, key);
}

// Function to print the node at a specific index
void printNodeAtIndex(LinkedList *list, int index) {
  Node *curr = list->head;
  int count = 0;
  while (curr) {
    if (count == index) {
      printf("%p\n", curr->data);
      return;
    }
    count++;
    curr = curr->next;
  }
  printf("Index out of bounds\n");
}

#endif
