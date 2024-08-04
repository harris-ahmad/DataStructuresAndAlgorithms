class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
        this.prev = null;
    }
}

class LinkedList {
    constructor() {
        this.head = null;
        this.tail = null;
        this.length = 0;
        this.nodeMap = new Map();
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
            this.head.prev = newNode;
            newNode.next = this.head;
            this.head = newNode;
        }
        this.nodeMap.set(data.id, newNode)
        this.length++;
    }

    append(data) {
        const newNode = new Node(data);
        if (!this.head) {
            this.head = newNode;
            this.tail = newNode;
        } else {
            this.tail.next = newNode;
            newNode.prev = this.tail;
            this.tail = newNode;
        }
        this.nodeMap.set(data.id, newNode);
        this.length++;
    }

    insertBetween(data, before, after) {
        const newNode = new Node(data);
        let curr = this.head;

        // finding the node with the `after` data
        while (curr && curr.data.id !== after.id) {
            curr = curr.next;
        }

        if (curr) {
            // finding the node with the `before` data
            let nextNode = curr.next;
            while (nextNode && nextNode.data.id !== before.id) {
                curr = nextNode;
                nextNode = nextNode.next;
            }

            // if the `before` node is found, insert the new node
            if (nextNode && nextNode.data.id === before.id) {
                newNode.next = nextNode;
                newNode.prev = curr;
                curr.next = newNode;
                nextNode.prev = newNode;
                this.nodeMap.set(data.id, newNode);
                this.length++;
            } else {
                throw Error("Before node not found");
            }
        } else {
            throw Error("After node not found");
        }
    }

    print() {
        let curr = this.head;
        let result = []
        while (curr) {
            result.push(curr.data.toString());
            curr = curr.next;
        }
        console.log(result.join(" <-> "));
    }
}

main()