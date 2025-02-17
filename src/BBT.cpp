#include <BBT.h>
#include <iostream>
#include <cmath>

template class BBT<int32_t, int32_t>;

template<typename K, typename V> void BBT<K,V>::insert(K key, V val) {
  if(head==nullptr) {
    head=new node(nullptr, nullptr, BALANCED, key, val);
    return;
  }
  node *currentNode = head;
  node *arr[50];
  balance dir[50];
  int32_t c=0;
  while(true) {
    arr[c]=currentNode;
    if(currentNode->key<key) {
      dir[c++]=RIGHT;
      if(currentNode->rptr==nullptr) {currentNode->rptr=new node(nullptr, nullptr, BALANCED, key, val);arr[c]=currentNode->rptr;break;}
      else currentNode=currentNode->rptr;
    } else if(currentNode->key>key) {
      dir[c++]=LEFT;
      if(currentNode->lptr==nullptr)  {currentNode->lptr=new node(nullptr, nullptr, BALANCED, key, val);arr[c]=currentNode->lptr;break;}
      else currentNode=currentNode->lptr;
    } else return;
  }
  dir[c]=BALANCED;
  int32_t m=-1;
  //f first ubal n from leaf up
  for(int32_t i = c-1; i>=0; --i) if(arr[i]->b!=BALANCED) {m=i;break;}
  // all b n below will be updated to dir taken
  for(int32_t i = m+1; i<c; ++i) arr[i]->b=dir[i];
  // con for do nothing either the path taken throught the tree was balanced all the way to the root(m=-1) or the first unbalanced node became balanced
  if(m==-1)return;
  if(arr[m]->key==1031) {
    std::cout << "halo";
  }
  else if(m+1<c) if (arr[m+1]->key==1031) {
    std::cout << "halo";
  }else if(m+2<c) if (arr[m+2]->key==1031) {
    std::cout << "halo";
  }
  if(arr[m]->b!=dir[m]){arr[m]->b=BALANCED;return;}
  //crit
  bool f=arr[m]->b==LEFT;
  if(arr[m+1]->b==arr[m]->b)/*case1*/ {
    (f?arr[m]->lptr:arr[m]->rptr)=(f?arr[m+1]->rptr:arr[m+1]->lptr);
    (f?arr[m+1]->rptr:arr[m+1]->lptr)=arr[m];
    arr[m]->b=BALANCED;
    arr[m+1]->b=BALANCED;
    if(m!=0) (dir[m-1]==LEFT?arr[m-1]->lptr:arr[m-1]->rptr)=arr[m+1];
    else head=arr[m+1];
  } else /*case2*/{
    (f?arr[m+1]->rptr:arr[m+1]->lptr)=(f?arr[m+2]->lptr:arr[m+2]->rptr);
    (f?arr[m]->lptr:arr[m]->rptr)=(f?arr[m+2]->rptr:arr[m+2]->lptr);
    arr[m+2]->lptr=(f?arr[m+1]:arr[m]);//
    arr[m+2]->rptr=(f?arr[m]:arr[m+1]);
    arr[m+2]->b=BALANCED;
    arr[m+1]->b=(f?BALANCED:dir[m+2]==BALANCED?BALANCED:dir[m+2]==LEFT?RIGHT:LEFT);
    arr[m]->b=(f?dir[m+2]==BALANCED?BALANCED:dir[m+2]==LEFT?RIGHT:LEFT:BALANCED);
    if(m!=0) (dir[m-1]==LEFT?arr[m-1]->lptr:arr[m-1]->rptr)=arr[m+2];
    else head=arr[m+2];
  }
}

template<typename K, typename V> void BBT<K, V>::traverse(BBT<K,V>::node *n) {
  if(n==nullptr) return;
  std::cout << "(" << n->key;
  traverse(n->lptr);
  traverse(n->rptr);
  std::cout << ")";
}

template<typename K, typename V> int32_t BBT<K, V>::search(K key) {
  node *cNode = head;
  while(true)
    if(cNode->key==key) {return cNode->key;}
    else if(key<cNode->key) if(cNode->lptr!=nullptr) cNode=cNode->lptr; else return -1;
    else if(cNode->rptr!=nullptr) cNode=cNode->rptr; else return -1;
}
