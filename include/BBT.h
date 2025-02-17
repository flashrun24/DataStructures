#ifndef DATASTRUCTURES_BBT
#define DATASTRUCTURES_BBT
#include <cstdint>

template<typename K, typename V>
class BBT {
public:
  enum balance {
    BALANCED,
    LEFT,
    RIGHT
  };
  struct node {
    node *lptr;
    node *rptr;
    balance b{BALANCED};
    K key;
    V value;
  };
  void insert(K key, V val);
  void traverse(node *n);
  int32_t search(K key);
  node *head = nullptr;
};

#endif
