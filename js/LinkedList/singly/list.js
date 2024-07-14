class Node {
  constructor(data) {
    this.data = data;
    this.next = null;
  }
};

class LinkedList {
  constructor() {
    this.head = null;
  }

  getHead() {
    return this.head;
  }

  getTail() {
    let lastNode = this.head;
    while (lastNode & lastNode.next) {
      lastNode = lastNode.next;
    }
    return lastNode;
  }
};