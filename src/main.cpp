#include <iostream>
#include "Config.h"
#include <cstdint>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <chrono>
#include "BBT.h"

const int32_t n = 4;

int32_t dist[n][n] = {
  {0, 10000,-2, 10000},
  {4, 0, 3, 10000},
  {10000, 10000, 0, 2},
  {10000,-1, 10000, 0}
};

int32_t prev[n][n];

void warshall() {
  for(int32_t i = 0; i<n; ++i) for(int32_t j = 0; j<n; ++j) prev[i][j]=dist[i][j]!=10000?i:n; 
  for(int32_t k = 0; k<n; ++k) for(int32_t i = 0; i<n; ++i) {
    for(int32_t j = 0; j<n; ++j) if(dist[i][j]>dist[i][k]+dist[k][j]) {
      dist[i][j]=dist[i][k]+dist[k][j];
      prev[i][j]=prev[k][j];
    }
  }
}
void path(int32_t u, int32_t v) {
  std::vector<int32_t> p;
  if(prev[u][v]==n) return;
  p.emplace(p.begin(), v);
  while(u!=v) {
    v=prev[u][v];
    p.emplace(p.begin(), v);
  }
  for(int32_t i = 0; i<p.size()-1; ++i) std::cout << 1+p[i] << ", ";
  std::cout << 1+p[p.size()-1];
}

#define N_NODES 6

int32_t adjecency[N_NODES][N_NODES] = {
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
};

typedef struct node {
  int32_t v;
  int32_t parent = N_NODES;
  bool explored = false;
} node;
std::queue<int32_t> bfsQ;
node nodes[N_NODES];

int32_t goalNode = 5;

node bfs(int32_t root) {
  nodes[root].explored = true;
  bfsQ.push(root);
  while(!bfsQ.empty()) {
    int32_t t = bfsQ.front();
    if(t==goalNode) return nodes[t];
    for(int32_t i = 0; i<N_NODES; ++i) if(adjecency[t][i]==1&&!nodes[i].explored) {
      nodes[i].explored = true;
      nodes[i].parent = t;
      bfsQ.push(i);
    }
  }
  return nodes[root];
}

void dfs() {

}

void randomArr(int32_t *arr, std::size_t s) {
  for(int32_t i = 0; i<s; ++i) arr[i]=i;
  for(int32_t sPos=s-1; sPos>0;) {
    int32_t rPos = (int32_t)((((double)std::rand())/RAND_MAX)*sPos);
    int32_t tmp = arr[sPos];
    arr[sPos--]=arr[rPos];
    arr[rPos]=tmp;
  }
}

int main() {
#define N 1150
  std::cout<<PROJECT_NAME<<" ";
  std::cout<<VERSION_MAJOR<<"."<<VERSION_MINOR<<std::endl;
  BBT<int32_t, int32_t> tree;
  std::map<int32_t, int32_t> m;
  int32_t a[N];
  randomArr(a, N);
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
  std::chrono::time_point<std::chrono::high_resolution_clock> end;
  start = std::chrono::high_resolution_clock::now();
  int64_t s = 0;
  for(int32_t i =0;i<N;++i) {
    if (a[i]==1028) {
      std::cout << "hello" << std::endl;
      tree.insert(a[i],a[i]);
      int64_t k = 0;
      for(int32_t j =0;j<=i;++j)  k+=tree.search(a[j]);
      if(k!=s) std::cout << "failed at: " << i << ", " << a[i] << std::endl;
    }
    else tree.insert(a[i],a[i]);
    s+=a[i];
  }
  end = std::chrono::high_resolution_clock::now();
  std::cout << "My time: " << (end-start).count() << std::endl;
  //start = std::chrono::high_resolution_clock::now();
  //for(int32_t i =0;i<N;++i)  m[a[i]]=a[i];
  //int64_t v = 0;
  //for(int32_t i =0;i<N;++i)  v+=m.at(i);
  //end = std::chrono::high_resolution_clock::now();
  //std::cout << "Map time: " << (end-start).count() << std::endl;
  //std::cout << "bintreesum: " << k  << " mapsum: " << v << " actualsum: " << (int64_t)((((int64_t)N-1)*((int64_t)N))/2) << std::endl;
  return 0;
}
