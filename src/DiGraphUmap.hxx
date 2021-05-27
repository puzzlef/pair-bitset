#pragma once
#include <vector>
#include <unordered_map>
#include <ostream>
#include <iostream>
#include "_main.hxx"

using std::vector;
using std::unordered_map;
using std::ostream;
using std::cout;




// DI-GRAPH (UNORDERED MAP)
// ------------------------

template <class V=NONE, class E=NONE>
class DiGraphUmap {
  public:
  using TVertex = V;
  using TEdge   = E;

  private:
  vector<bool> vex;
  vector<V>    vdata;
  vector<unordered_map<int, E>> edata;
  unordered_map<int, E>         none;
  int N = 0, M = 0;

  // Cute helpers
  private:
  int  s() const { return vex.size(); }
  bool eex(int u, int v) const { return edata[u].count(v); }

  // Read operations
  public:
  int span()  const { return s(); }
  int order() const { return N; }
  int size()  const { return M; }

  bool hasVertex(int u)      const { return u < s() && vex[u]; }
  bool hasEdge(int u, int v) const { return u < s() && eex(u, v); }
  auto edges(int u)          const { return u < s()? keys(edata[u])  : keys(none); }
  int degree(int u)          const { return u < s()? edata[u].size() : 0; }
  auto vertices()      const { return filter(range(s()), [&](int u) { return  vex[u]; }); }
  auto nonVertices()   const { return filter(range(s()), [&](int u) { return !vex[u]; }); }
  auto inEdges(int v)  const { return filter(range(s()), [&](int u) { return eex(u, v); }); }
  int inDegree(int v) const { return countIf(range(s()), [&](int u) { return eex(u, v); }); }

  V vertexData(int u)   const { return hasVertex(u)? vdata[u] : V(); }
  void setVertexData(int u, V d) { if (hasVertex(u)) vdata[u] = d; }
  E edgeData(int u, int v)   const { return hasEdge(u, v)? edata[u][v] : E(); }
  void setEdgeData(int u, int v, E d) { if (hasEdge(u, v)) edata[u][v] = d; }

  // Write operations
  public:
  void addVertex(int u, V d=V()) {
    if (hasVertex(u)) return;
    if (u >= s()) {
      vex.resize(u+1);
      vdata.resize(u+1);
      edata.resize(u+1);
    }
    vex[u] = true;
    vdata[u] = d;
    N++;
  }

  void addEdge(int u, int v, E d=E()) {
    if (hasEdge(u, v)) return;
    addVertex(u);
    addVertex(v);
    edata[u][v] = d;
    M++;
  }

  void removeEdge(int u, int v) {
    if (!hasEdge(u, v)) return;
    edata[u].erase(v);
    M--;
  }

  void removeEdges(int u) {
    if (!hasVertex(u)) return;
    M -= degree(u);
    edata[u].clear();
  }

  void removeInEdges(int v) {
    if (!hasVertex(v)) return;
    for (int u : inEdges(v))
      removeEdge(u, v);
  }

  void removeVertex(int u) {
    if (!hasVertex(u)) return;
    removeEdges(u);
    removeInEdges(u);
    vex[u] = false;
    N--;
  }
};




// DI-GRAPH PRINT
// --------------


template <class V, class E>
void write(ostream& a, const DiGraphUmap<V, E>& x, bool all=false) {
  a << "order: " << x.order() << " size: " << x.size();
  if (!all) { a << " {}"; return; }
  a << " {\n";
  for (int u : x.vertices()) {
    a << "  " << u << " ->";
    for (int v : x.edges(u))
      a << " " << v;
    a << "\n";
  }
  a << "}";
}

template <class V, class E>
void print(const DiGraphUmap<V, E>& x, bool all=false) { write(cout, x, all); }

template <class V, class E>
void println(const DiGraphUmap<V, E>& x, bool all=false) { print(x, all); cout << "\n"; }
