#include "sdb.h"
#include <iostream>
#include <stdexcept>

template <typename T> sdb::aetrix<T>::aetrix(int r, int c) {
  rows = r, cols = c;
  makeAetrix();
}

template <typename T> sdb::aetrix<T>::~aetrix() { clearAetrix(); }

template <typename T>
typename sdb::aetrix<T>::node *
sdb::aetrix<T>::makeNode(std::array<int, 2> cords, T data) {
  node *no = new node(cords);
  no->data = -1;
  lookup[cords] = no;
  return no;
}

template <typename T> int sdb::aetrix<T>::cordsInt(std::array<int, 2> cords) {
  std::string cat = std::to_string(cords[0]) + std::to_string(cords[1]);
  return (std::stoi(cat));
}

template <typename T> void sdb::aetrix<T>::mapDirs() {}

template <typename T>
typename sdb::aetrix<T>::node *
sdb::aetrix<T>::returnNode(std::array<int, 2> cords) {
  return (lookup[cords]);
}

template <typename T> T &sdb::aetrix<T>::operator[](std::array<int, 2> cords) {
  node *result = lookup[cords];
  if ((cords[0] > rows) || (cords[1] > cols) || (cords[0] <= 0) ||
      (cords[1] <= 0)) {
    throw std::out_of_range("Index not in range of aetrix.");
  } else if (result == nullptr) {
    makeNode(cords, T());
    result = lookup[cords];
  }

  return (result->data);
};

template <typename T>
const T &sdb::aetrix<T>::operator[](std::array<int, 2> cords) const {
  const node *result = returnNode(cords);
  if (result == nullptr) {
    throw std::out_of_range("Index not in range of aetrix. (Doesn't exist)");
  }
  return (result->data);
};

template <typename T> void sdb::aetrix<T>::makeAetrix() {
  core = new node(coreCords);
  node *cur = core;

  // Create the matrix with the specified number of rows and cols
  for (int i = 1; i <= rows; i++) {
    cur->down = makeNode({i, 1});
    cur = cur->down;
    for (int j = 1; j <= cols; j++) {
      cur->right = makeNode({i, j});
      cur = cur->right;
    }
  }
}

template <typename T> void sdb::aetrix<T>::clearAetrix() { lookup.clear(); }

template <typename T>
void sdb::aetrix<T>::convCords(std::array<int, 2> &cords) {
  if (cords[0] == 0)
    cords[0] += 1;
  if (cords[1] == 0)
    cords[1] += 1;
}

/* template <typename T> */
/* // Assignment operator to initialize the matrix with values */
/* T &sdb::aetrix<T>::operator=( */
/*     std::initializer_list<std::initializer_list<T>> initList) { */
/*   // Clear existing data */
/*   data.clear(); */

/*   int rowIndex = 0; */
/*   for (const auto &row : initList) { */
/*     int colIndex = 0; */
/*     for (const auto &val : row) { */
/*       data[{rowIndex, colIndex}] = val; */
/*       colIndex++; */
/*     } */
/*     rowIndex++; */
/*   } */

/*   return *this; */
/* } */
