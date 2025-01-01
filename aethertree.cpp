#include "sdb.h"
#include <iostream>

template <typename F> sdb::aethertree<F>::aethertree() {
  static const leaf *core = nullptr;
}

template <typename F>
typename sdb::aethertree<F>::leaf *sdb::aethertree<F>::linkLeaf(int key,
                                                                F value) {
  leaf *n = new leaf(key, value);
  n->left = nullptr;
  n->right = nullptr;

  return n;
}

template <typename F> void sdb::aethertree<F>::forgeLeaf(int key, F value) {
  forgeLeafP(key, value, core);
}

template <typename F>
void sdb::aethertree<F>::forgeLeafP(int key, F value, leaf *Cur) {
  // If the core is nullptr then the tree is empty, so create the root leaf
  if (core == nullptr) {
    core = linkLeaf(key, value);
  } else if (key < Cur->key) { // Left leaf

    // If left leaf exists keep traversing
    if (Cur->left != nullptr) {
      forgeLeafP(key, value, Cur->left);
    } else {
      Cur->left = linkLeaf(key, value);
    }

  } else if (key > Cur->key) { // Right leaf

    // If right leaf exists keep traversing
    if (Cur->right != nullptr) {
      forgeLeafP(key, value, Cur->right);
    } else {
      Cur->right = linkLeaf(key, value);
    }
  } else {
    std::cout << "Key " << key << "already added" << std::endl;
  }
}

template <typename F>
typename sdb::aethertree<F>::leaf *sdb::aethertree<F>::returnLeaf(int key) {
  return returnLeafP(key, core);
}

template <typename F>
typename sdb::aethertree<F>::leaf *sdb::aethertree<F>::returnLeafP(int key,
                                                                   leaf *Cur) {
  if (Cur != nullptr) {
    if (Cur->key == key) {
      return Cur;
    } else {
      if (key < Cur->key) {
        return returnLeafP(key, Cur->left);
      } else {
        return returnLeafP(key, Cur->right);
      }
    }
  } else {
    return nullptr;
  }
}

template <typename F> int sdb::aethertree<F>::findSmallest() {
  return findSmallestP(core);
}

template <typename F> int sdb::aethertree<F>::findSmallestP(leaf *Cur) {
  if (core == nullptr) {
    std::cout << "The tree is empty. Cannot find smallest. ERR: -1"
              << std::endl;
    return -1;
  } else {
    if (Cur->left != nullptr) {
      return findSmallestP(Cur->left);
    } else {
      return Cur->key;
    }
  }
}

template <typename F>
// Overloaded subscript operator []
F &sdb::aethertree<F>::operator[](int key) {
  leaf *result = returnLeafP(key, core);
  if (result == nullptr) {
    insertLeaf(key, F());
    result = returnLeafP(key, core);
  }
  return result->value;
}

template <typename F>
// Const version of the subscript operator []
const F &sdb::aethertree<F>::operator[](int key) const {
  const leaf *result = returnLeafP(key, core);
  if (result == nullptr) {
    // Handle the case where the key doesn't exist in the tree.
    throw std::out_of_range("Key not found in the binary search tree.");
  }
  return result->value;
}

template <typename F>
void sdb::aethertree<F>::insertLeaf(int key, const F &value) {
  core = insertLeafP(key, value, core);
}

template <typename F>
typename sdb::aethertree<F>::leaf *
sdb::aethertree<F>::insertLeafP(int key, const F &value, leaf *Cur) {
  if (Cur == nullptr) {
    // The current node is null (empty subtree).
    // Create a new leaf node with the given key and value.
    return new leaf(key, value);
  }

  if (key < Cur->key) {
    // If the key is less than the current node's key, insert in the left
    // subtree.
    Cur->left = insertLeafP(key, value, Cur->left);
  } else if (key > Cur->key) {
    // If the key is greater than the current node's key, insert in the right
    // subtree.
    Cur->right = insertLeafP(key, value, Cur->right);
  } else {
    // If the key already exists in the tree, update the value.
    Cur->value = value;
  }

  // Return the modified current node.
  return Cur;
}

template <typename F> void sdb::aethertree<F>::clear() {
  clearTree(core);
  core = nullptr;
}

template <typename F> void sdb::aethertree<F>::clearTree(leaf *Cur) {
  if (Cur == nullptr) {
    return;
  }

  clearTree(Cur->left);
  clearTree(Cur->right);

  delete Cur;
}

template <typename F> bool sdb::aethertree<F>::remove(int key) {
  return removeNode(core, key);
}

template <typename F> bool sdb::aethertree<F>::removeP(leaf *&Cur, int key) {
  if (Cur == nullptr) {
    return false;
  }

  if (key < Cur->key) {
    // If the key is less than the current node's key, search in the left
    // subtree.
    return removeNode(Cur->left, key);
  } else if (key > Cur->key) {
    // If the key is greater than the current node's key, search in the right
    // subtree.
    return removeNode(Cur->right, key);
  } else {
    // Found the node to be deleted.

    if (Cur->left == nullptr) {
      leaf *temp = Cur->right;
      delete Cur;
      Cur = temp;
    } else if (Cur->right == nullptr) {
      leaf *temp = Cur->left;
      delete Cur;
      Cur = temp;
    } else {
      // Case 2: Node has two children.
      leaf *minNode = findSmallestP(Cur->right);
      Cur->key = minNode->key;
      Cur->value = minNode->value;
      removeNode(Cur->right, minNode->key);
    }

    // Node successfully removed.
    return true;
  }
}
