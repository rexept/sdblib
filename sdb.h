#include <array>
#include <map>
#include <utility>
#include <vector>

namespace sdb {

/**
 * A data structure that hold key value pairs in a tree-like arrangment.
 **/
template <typename F> class aethertree {
private:
  struct leaf {
    int key;
    F value;
    leaf *left;
    leaf *right;
    leaf(int k, const F &v) : key(k), value(v), left(nullptr), right(nullptr) {}
  };
  leaf *core = nullptr;

  void forgeLeafP(int key, F value, leaf *Cur);
  leaf *returnLeafP(int key, leaf *Cur);
  int findSmallestP(leaf *Cur);
  leaf *insertLeafP(int key, const F &value, leaf *Cur);
  leaf *linkLeaf(int key, F value);
  void forgeLeaf(int key, F value);
  void insertLeaf(int key, const F &value);
  void clearTree(leaf *Cur);
  bool removeP(leaf *&Cur, int key);

public:
  aethertree();

  leaf *returnLeaf(int key);
  int findSmallest();

  void clear();
  bool remove(int key);

  F &operator[](int key);
  const F &operator[](int key) const;
};

/* The SDB Matrix Data Structure */
template <typename T> class aetrix {
private:
  struct node {
    T data;
    std::array<int, 2> cords;
    node *up;
    node *down;
    node *left;
    node *right;

    node(std::array<int, 2> cordz)
        : data(T()), cords(cordz), left(nullptr), right(nullptr), up(nullptr),
          down(nullptr) {}
  };

  node *core;
  std::array<int, 2> coreCords = {-1, -1};
  int rows, cols;

  std::map<std::array<int, 2>, node *> lookup;

  // by not making data a * make throw error vvvvv
  node *makeNode(std::array<int, 2> cords, T data = T());
  node *returnNode(std::array<int, 2>);

  void makeAetrix();
  void clearAetrix();

  int cordsInt(std::array<int, 2> cords);
  void convCords(std::array<int, 2> &cords);
  void mapDirs();

public:
  aetrix(int r, int c);
  ~aetrix();

  T &operator[](std::array<int, 2> cords);
  const T &operator[](std::array<int, 2> cords) const;
  T &operator=(std::initializer_list<std::initializer_list<T>> initList);
};

}; // namespace sdb
