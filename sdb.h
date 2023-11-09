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
