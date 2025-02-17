#include "Stack.h"
#include <cstdint>
#include <string>

template class Stack<std::string>;
template class Stack<int32_t>;
template<typename data> Stack<data>::~Stack() {
  while(!isEmpty()) pop();
}
template<typename data> void Stack<data>::push(data v) {
  struct node *tmp = this->top;
  struct node *n = new node();
  n->value = v;
  n->nextNode = tmp;
  this->top = n;
};
template<typename data> data Stack<data>::pop() {
  data v = top->value;
  node *tmp = top;
  this->top = this->top->nextNode;
  delete tmp;
  return v;
};
template<typename data> bool Stack<data>::isEmpty() {
  return this->top==nullptr;
};
