import { expect } from 'chai';
import LinkedList from "./list.mjs";

describe('LinkedList', () => {
  let list;

  beforeEach(() => {
    list = new LinkedList();
  });

  describe('getHead', () => {
    it('should return null for an empty list', () => {
      expect(list.getHead()).to.be.null;
    });

    it('should return the head node of the list', () => {
      list.prepend({ id: 1, value: 'first' });
      expect(list.getHead().data).to.deep.equal({ id: 1, value: 'first' });
    });
  });

  describe('getTail', () => {
    it('should return null for an empty list', () => {
      expect(list.getTail()).to.be.null;
    });

    it('should return the tail node of the list', () => {
      list.append({ id: 1, value: 'first' });
      expect(list.getTail().data).to.deep.equal({ id: 1, value: 'first' });
    });
  });

  describe('prepend', () => {
    it('should add a node to the beginning of the list', () => {
      list.prepend({ id: 1, value: 'first' });
      expect(list.getHead().data).to.deep.equal({ id: 1, value: 'first' });
      expect(list.size()).to.equal(1);
    });

    it('should correctly update the head and tail for the first node', () => {
      list.prepend({ id: 1, value: 'first' });
      expect(list.getHead().data).to.deep.equal({ id: 1, value: 'first' });
      expect(list.getTail().data).to.deep.equal({ id: 1, value: 'first' });
    });
  });

  describe('append', () => {
    it('should add a node to the end of the list', () => {
      list.append({ id: 1, value: 'first' });
      expect(list.getTail().data).to.deep.equal({ id: 1, value: 'first' });
      expect(list.size()).to.equal(1);
    });

    it('should correctly update the tail when appending nodes', () => {
      list.append({ id: 1, value: 'first' });
      list.append({ id: 2, value: 'second' });
      expect(list.getTail().data).to.deep.equal({ id: 2, value: 'second' });
    });
  });

  describe('insertBetween', () => {
    it('should insert a node between two nodes', () => {
      list.append({ id: 1, value: 'first' });
      list.append({ id: 3, value: 'third' });
      list.insertBetween({ id: 2, value: 'second' }, { id: 3, value: 'third' }, { id: 1, value: 'first' });
      expect(list.find(2).data).to.deep.equal({ id: 2, value: 'second' });
    });
  });

  describe('deleteHead', () => {
    it('should delete the head node of the list', () => {
      list.append({ id: 1, value: 'first' });
      list.deleteHead();
      expect(list.getHead()).to.be.null;
    });
  });

  describe('deleteTail', () => {
    it('should delete the tail node of the list', () => {
      list.append({ id: 1, value: 'first' });
      list.deleteTail();
      expect(list.getTail()).to.be.null;
    });
  });

  describe('deleteAny', () => {
    it('should delete any node matching the target data', () => {
      list.append({ id: 1, value: 'first' });
      list.append({ id: 2, value: 'second' });
      list.deleteAny({ id: 1 });
      expect(list.find(1)).to.be.null;
    });
  });

  describe('size', () => {
    it('should return the correct size of the list', () => {
      list.append({ id: 1, value: 'first' });
      list.append({ id: 2, value: 'second' });
      expect(list.size()).to.equal(2);
    });
  });

  describe('reverseList', () => {
    it('should reverse the linked list', () => {
      list.append({ id: 1, value: 'first' });
      list.append({ id: 2, value: 'second' });
      list.reverseList();
      expect(list.getHead().data).to.deep.equal({ id: 2, value: 'second' });
    });
  });

  describe('find', () => {
    it('should find a node by its id', () => {
      list.append({ id: 1, value: 'first' });
      expect(list.find(1).data).to.deep.equal({ id: 1, value: 'first' });
    });

    it('should return null if the node is not found', () => {
      expect(list.find(999)).to.be.null;
    });
  });

  describe('clear', () => {
    it('should clear the list and remove all nodes', () => {
      list.append({ id: 1, value: 'first' });
      list.clear();
      expect(list.getHead()).to.be.null;
      expect(list.size()).to.equal(0);
    });
  });
});
