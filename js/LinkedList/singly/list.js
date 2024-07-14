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

  prepend(data) {
    const newNode = new Node(data);
    newNode.next = this.head;
    this.head = newNode;
  }

  append(data) {
    const newNode = new Node(data);
    if (!this.head) {
      this.head = newNode;
    } else {
      const lastNode = this.getTail();
      lastNode.next = newNode;
    }
  }

  insertBetween(data, after) {
    const newNode = new Node(data);
    let prevNode = this.head;

    while (prevNode && prevNode.data !== after) {
      prevNode = prevNode.next;
    }

    if (prevNode) {
      newNode.next = prevNode.next;
      prevNode.next = newNode;
    }
  }

  deleteHead() {
    if (!this.head) {
      return new Error("list is empty, nothing to delete");
    }
    if (this.head) {
      this.head = this.head = next;
    }
  }

  deleteTail() {
    if (!this.head) {
      return new Error("list is empty, nothing to delete");
    }
    if (!this.head.next) {
      this.head = null;
    } else {
      let prevNode = this.head;
      while (prevNode.next && prevNode.next.next) {
        prevNode = prevNode.next;
      }
      prevNode.next = null;
    }
  }

  deleteAny(target) {
    if (!this.head) {
      return;
    }

    if (this.head.data === target) {
      this.head = this.head.next;
    } else {
      let prevNode = this.head;
      let curr = this.head.next;

      while (curr && curr.data !== target) {
        prevNode = curr;
        curr = curr.next;
      }

      if (curr) {
        prevNode.next = curr.next;
      }
    }
  }

  size() {
    let count = 0;
    let curr = this.head;
    while (curr) {
      count++;
      curr = curr.next;
    }
    return count;
  }

  reverseList() {
    let prev = null;
    let curr = this.head;
    while (curr) {
      const next = curr.next;
      curr.next = prev;
      prev = curr;
      curr = next;
    }
    this.head = prev;
  }
};