class TreeNode {
  constructor(value, left, right) {
    this.value = value;
    this.left = left;
    this.right = right;
  }

  show() {
    return this.value;
  }
}

class BST {
  constructor() {
    this.root = null;
  }

  getMin() {
    let current = this.root;
    while(current.left !== null) {
      current = current.left;
    }
    return current.show();
  }

  getMax() {
    let current = this.root;
    while(current.right !== null) {
      current = current.right;
    }
    return current.show();
  }

  find(value) {
    let current = this.root;
    while(current !== null) {
      if (value === current.value) {
        return current;
      } else if (value < current.value) {
        current = current.left;
      } else {
        current = current.right;
      }
    }
    return null;
  }

  insert(value) {
    const n = new TreeNode(value, null, null);
    if (this.root === null) {
      this.root = n;
    } else {
      let current = this.root;
      let parent;
      while(true) {
        parent = current;
        if (value < current.value) {
          current = current.left;
          if (current === null) {
            parent.left = n;
            break;
          }
        } else {
          current = current.right;
          if (current === null) {
            parent.right = n;
            break;
          }
        }
      }
    }
  }

  midOrder(node) {
    if (node !== null) {
      this.midOrder(node.left);
      console.log(node.show());
      this.midOrder(node.right);
    }
  }

  preOrder(node) {
    if (node !== null) {
      console.log(node.show());
      this.preOrder(node.left);
      this.preOrder(node.right);
    }
  }

  postOrder(node) {
    if (node !== null) {
      this.postOrder(node.left);
      this.postOrder(node.right);
      console.log(node.show());
    }
  }
}

const t = new BST();

t.insert(1);
t.insert(25);
t.insert(3);
t.insert(-1);
t.insert(8);

t.midOrder(t.root);
console.log('\n');
t.preOrder(t.root);
console.log('\n');
t.postOrder(t.root);

console.log(t.getMin());
console.log(t.getMax());
console.log(t.find(25));
console.log(t.find(4));
