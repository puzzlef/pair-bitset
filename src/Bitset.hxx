#pragma once
#include "_main.hxx"
#include <utility>
#include <array>
#include <vector>
#include <iterator>
#include <algorithm>

using std::pair;
using std::array;
using std::vector;
using std::iter_swap;
using std::copy;
using std::find_if;
using std::back_inserter;




template <class T=NONE, size_t C=128>
class Bitset {
  // Member types.
  public:
  using entry = pair<int, T>;

  // Data.
  protected:
  size_t N = 0;
  vector<entry> large;
  array<entry, C> small;


  // Cute helpers.
  private:
  inline bool isSmall() const { return large.size() == 0; }
  inline       auto begin()       { return isSmall()? small.data() : large.data(); }
  inline const auto begin() const { return isSmall()? small.data() : large.data(); }
  inline       auto end()       { return isSmall()? small.data()+N : large.data()+N; }
  inline const auto end() const { return isSmall()? small.data()+N : large.data()+N; }
  inline       auto iterable()       { return pointerIter(begin(), end()); }
  inline const auto iterable() const { return pointerIter(begin(), end()); }

  inline auto lookup(int id) const {
    auto fe = [&](const auto& e) { return e.first == id; };
    return find_if(begin(), end(), fe);
  }

  inline void pushBackExpand(const entry& e) {
    copy(small.begin(), small.end(), back_inserter(large));
    large.push_back(e); N++;
  }

  inline void pushBack(const entry& e) {
    if (isSmall()) {
      if (N<C) small[N++] = e;
      else pushBackExpand(e);
    }
    else { large.push_back(e); N++; }
  }

  inline void popBack() {
    if (!isSmall()) large.pop_back();
    N--;
  }

  // Read as iterable.
  public:
  auto entries() const { return transformIter(iterable(), [](const auto& e) { return e; }); }
  auto keys()    const { return transformIter(iterable(), [](const auto& e) { return e.first; }); }
  auto values()  const { return transformIter(iterable(), [](const auto& e) { return e.second; }); }

  // Read operations.
  public:
  size_t size()      const { return N; }
  bool   has(int id) const { return lookup(id)!=end(); }
  T      get(int id) const { auto it = lookup(id); return it==end()? T() : (*it).second; }

  // Write operations
  public:
  void clear() {
    large.clear();
    N = 0;
  }

  void set(int id, T v) {
    auto it = lookup(id);
    if (it==end()) return;
    (*it).second = v;
  }

  void add(int id, T v=T()) {
    if (!has(id)) pushBack({id, v});
  }

  void remove(int id) {
    auto it = lookup(id);
    if (it==end()) return;
    iter_swap(it, end()-1);
    popBack();
  }
};
