#ifndef DATASTRUCTURES_STACK
#define DATASTRUCTURES_STACK

template<typename data>
class Stack {
  private:
    struct node {
      data value;
      node *nextNode;
    };
    struct node *top = nullptr;
  public:
    ~Stack();
    void push(data value);
    data pop();
    bool isEmpty();
};

#endif
