using namespace std;

#include <iostream>
#include <vector>

template <typename T>
class Node {
 public:
  T data;
  Node<T>*left, *right;
  Node(T data) {
    this->data = data;
    left = right = NULL;
  }
};

template <typename T>
class Tree {
 private:
  Node<T> getNodeHelper(Node<T>* current, T target) {
    return target == current->data ? current
           : target < current->data && current->left
               ? getNodeHelper(current->left, target)
           : target > current->data && current->right
               ? getNodeHelper(current->right, target)
               : NULL;
  }

  Node<T> findNodeHelper(Node<T>* current, T target) {
    bool found = false;
    if (target == current->data) {
      found = true;
    } else if (target < current->data && current->left) {
      return findNodeHelper(current->left, target);
    } else if (target > current->data && current->right) {
      return findNodeHelper(current->right, target);
    }

    return found;
  }

  int heightHelper(Node<T>* current, int height = 0) {
    if (!current) {
      return height;
    } else {
      int leftHeight = heightHelper(current->left, height + 1);
      int rightHeight = heightHelper(current->right, height + 1);
      return leftHeight > rightHeight ? leftHeight : rightHeight;
    }
  }

  int sizeHelper(Node<T>* current, int size = 0) {
    if (!current) {
      return size;
    } else {
      int leftSize = sizeHelper(current->left, size + 1);
      int rightSize = sizeHelper(current->right, size + 1);
      return leftSize + rightSize;
    }
  }

  vector<Node<T>> getChildrenHelper(Node<T>* start, T key,
                                    vector<Node<T>> children) {
    if (start.data == key) {
      if (start->left && start->right) {
        children.push_back(start->left);
        children.push_back(start->right);
      }

      if (!start->left && !start->right) {
        return children;
      }

      if (!start->left && start->right) {
        children.push_back(start->right);
      } else if (start->left && !start->right) {
        children.push_back(start->left);
      }
    } else if (key < start->data && start->left) {
      getChildrenHelper(start->left, key, children);
    } else if (key > start->data && start->right) {
      getChildrenHelper(start->right, key, children);
    }

    return children;
  }

  void insertHelper(Node<T>* current, T data) {
    Node<T>* newNode = new Node<T>(data);
    if (!current) {
      root = newNode;
    } else {
      if (data < current->data) {
        if (current->left) {
          insertHelper(current->left, data);
        } else {
          current->left = newNode;
        }
      } else if (data > current->data) {
        if (current->right) {
          insertHelper(current->right, data);
        } else {
          current->right = newNode;
        }
      }
    }
  }

  vector<T> inOrderHelper(Node<T>* root, vector<T>& vec) {
    if (root) {
      if (root->left) {
        inOrderHelper(root->left, vec);
      }

      vec.push_back(root->data);

      if (root->right) {
        inOrderHelper(root->right, vec);
      }
    }
  }

  vector<T> preOrderHelper(Node<T>* root, vector<T>& vec) {
    if (root) {
      vec.push_back(root->data);

      if (root->left) {
        preOrderHelper(root->left, vec);
      }

      if (root->right) {
        preOrderHelper(root->right, vec);
      }
    }
  }

  vector<T> postOrderHelper(Node<T>* root, vector<T>& vec) {
    if (root) {
      if (root->left) {
        postOrderHelper(root->left, vec);
      }

      if (root->right) {
        postOrderHelper(root->right, vec);
      }

      vec.push_back(root->data);
    }
  }

 public:
  Node<T>* root;

  Tree() { root = NULL; }

  vector<T> inOrder() {
    vector<T> vec;
    inOrderHelper(root, &vec);
    return vec;
  }

  vector<T> preOrder() {
    vector<T> vec;
    preOrderHelper(root, &vec);
    return vec;
  }

  vector<T> postOrder() {
    vector<T> vec;
    postOrderHelper(root, &vec);
    return vec;
  }
};