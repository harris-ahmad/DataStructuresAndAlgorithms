class Node {
  constructor(data) {
    this.data = data;
    this.next = null;
  }
}

class LinkedList {
  constructor() {
    this.head = null;
    this.tail = null;
    this.length = 0;
    this.nodeMap = new Map();  // HashMap for O(1) lookups
  }

  getHead() {
    return this.head;
  }

  getTail() {
    return this.tail;
  }

  prepend(data) {
    const newNode = new Node(data);
    if (!this.head) {
      this.head = newNode;
      this.tail = newNode;
    } else {
      newNode.next = this.head;
      this.head = newNode;
    }
    this.nodeMap.set(data.id, newNode);
    this.length++;
  }

  append(data) {
    const newNode = new Node(data);
    if (!this.head) {
      this.head = newNode;
      this.tail = newNode;
    } else {
      this.tail.next = newNode;
      this.tail = newNode;
    }
    this.nodeMap.set(data.id, newNode);
    this.length++;
  }

  insertBetween(data, before, after) {
    const newNode = new Node(data);
    let curr = this.head;

    while (curr && curr.data !== after) {
      curr = curr.next;
    }

    if (curr && curr.next && curr.next.data === before) {
      newNode.next = curr.next;
      curr.next = newNode;
      this.nodeMap.set(data.id, newNode);
      this.length++;
    }
  }

  deleteHead() {
    if (this.head) {
      this.nodeMap.delete(this.head.data.id);
      this.head = this.head.next;
      if (!this.head) {
        this.tail = null;
      }
      this.length--;
    }
  }

  deleteTail() {
    if (!this.head) {
      return;
    }
    if (!this.head.next) {
      this.nodeMap.delete(this.head.data.id);
      this.head = null;
      this.tail = null;
    } else {
      let prevNode = this.head;
      while (prevNode.next && prevNode.next.next) {
        prevNode = prevNode.next;
      }
      this.nodeMap.delete(prevNode.next.data.id);
      prevNode.next = null;
      this.tail = prevNode;
    }
    this.length--;
  }

  deleteAny(target) {
    if (!this.head) {
      return;
    }

    if (this.head.data.id === target.id) {
      this.nodeMap.delete(this.head.data.id);
      this.head = this.head.next;
      if (!this.head) {
        this.tail = null;
      }
      this.length--;
    } else {
      let prevNode = this.head;
      let curr = this.head.next;

      while (curr && curr.data.id !== target.id) {
        prevNode = curr;
        curr = curr.next;
      }

      if (curr) {
        prevNode.next = curr.next;
        if (!curr.next) {
          this.tail = prevNode;
        }
        this.nodeMap.delete(curr.data.id);
        this.length--;
      }
    }
  }

  size() {
    return this.length;
  }

  reverseList() {
    let prev = null;
    let curr = this.head;
    let next = null;

    this.tail = this.head;

    while (curr) {
      next = curr.next;
      curr.next = prev;
      prev = curr;
      curr = next;
    }
    this.head = prev;
  }

  find(id) {
    return this.nodeMap.get(id) || null;
  }

  clear() {
    this.head = null;
    this.tail = null;
    this.length = 0;
    this.nodeMap.clear();
  }

  print() {
    let curr = this.head;
    const result = [];
    while (curr) {
      result.push(curr.data.toString());
      curr = curr.next;
    }
    console.log(result.join(" -> "));
  }
}

module.exports = LinkedList;
