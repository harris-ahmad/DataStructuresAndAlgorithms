/**
 * Node class representing a single node in a singly linked list.
 */
class Node {
    /**
     * Create a Node.
     * @param {*} data - The data to be stored in the node.
     */
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

/**
* LinkedList class representing a singly linked list.
*/
class LinkedList {
    /**
     * Create an empty LinkedList.
     */
    constructor() {
        this.head = null;
        this.tail = null;
        this.length = 0;
        this.nodeMap = new Map();  // HashMap for O(1) lookups
    }

    /**
     * Get the head node of the list.
     * @return {Node|null} The head node or null if the list is empty.
     */
    getHead() {
        return this.head;
    }

    /**
     * Get the tail node of the list.
     * @return {Node|null} The tail node or null if the list is empty.
     */
    getTail() {
        return this.tail;
    }

    /**
     * Prepend a node to the beginning of the list.
     * @param {*} data - The data to be stored in the new node.
     */
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

    /**
     * Append a node to the end of the list.
     * @param {*} data - The data to be stored in the new node.
     */
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

    /**
     * Insert a node between two existing nodes in the list.
     * @param {*} data - The data to be stored in the new node.
     * @param {*} before - The data of the node before which to insert the new node.
     * @param {*} after - The data of the node after which to insert the new node.
     */
    insertBetween(data, before, after) {
        const newNode = new Node(data);
        let curr = this.head;

        console.log('Inserting node:', data, 'between nodes:', after, 'and', before);

        // Find the node with the `after` data
        while (curr && curr.data.id !== after.id) {
            curr = curr.next;
        }

        // Ensure we found the `after` node
        if (curr) {
            console.log('Found node after:', curr.data);

            // Find the node with the `before` data
            let nextNode = curr.next;
            while (nextNode && nextNode.data.id !== before.id) {
                curr = nextNode;
                nextNode = nextNode.next;
            }

            // Insert the new node if `before` node is found
            if (nextNode && nextNode.data.id === before.id) {
                console.log('Found node before:', nextNode.data);
                newNode.next = nextNode;
                curr.next = newNode;
                this.nodeMap.set(data.id, newNode);
                this.length++;
            } else {
                console.error('Before node not found');
            }
        } else {
            console.error('After node not found');
        }
    }

    /**
     * Delete the head node of the list.
     */
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

    /**
     * Delete the tail node of the list.
     */
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

    /**
     * Delete any node from the list that matches the given target data.
     * @param {*} target - The target data to match for deletion.
     */
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

    /**
     * Get the size of the list.
     * @return {number} The number of nodes in the list.
     */
    size() {
        return this.length;
    }

    /**
     * Reverse the linked list in place.
     */
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

    /**
     * Find a node by its id.
     * @param {number} id - The id of the node to find.
     * @return {Node|null} The node with the given id or null if not found.
     */
    find(id) {
        return this.nodeMap.get(id) || null;
    }

    /**
     * Clear the list, removing all nodes.
     */
    clear() {
        this.head = null;
        this.tail = null;
        this.length = 0;
        this.nodeMap.clear();
    }

    /**
     * Print the list data in a readable format.
     */
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

export default LinkedList;