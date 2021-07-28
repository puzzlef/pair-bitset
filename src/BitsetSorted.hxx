#pragma once
#include "_main.hxx"
#include <utility>
#include <vector>
#include <algorithm>

using std::pair;
using std::vector;
using std::lower_bound;




template <class T=NONE>
class BitsetSorted {
  vector<pair<int, T>> ids;

  // Cute helpers
  private:
  auto where(int id) const {
    auto fc = [](const auto& e, int id) { return e.first < id; };
    return lower_bound(ids.begin(), ids.end(), id, fc);
  }

  auto lookup(int id) const {
    auto it = where(id);
    return it != ids.end() && (*it).first == id? it : ids.end();
  }

  // Read as iterable.
  public:
  auto entries() const { return transform(ids, [](const auto& e) { return e; }); }
  auto keys()    const { return transform(ids, [](const auto& e) { return e.first; }); }
  auto values()  const { return transform(ids, [](const auto& e) { return e.second; }); }

  // Read operations.
  public:
  size_t size()      const { return ids.size(); }
  bool   has(int id) const { return lookup(id) != ids.end(); }
  T      get(int id) const { auto it = lookup(id); return it == ids.end()? T() : (*it).second; }

  // Write operations
  public:
  void clear() {
    ids.clear();
  }

  void set(int id, T v) {
    auto it = lookup(id);
    if (it == ids.end()) return;
    (*it).second = v;
  }

  void add(int id, T v=T()) {
    auto it = where(id);
    if (it != ids.end() && (*it).first == id) return;
    ids.insert(it, {id, v});
  }

  void remove(int id) {
    auto it = lookup(id);
    if (it == ids.end()) return;
    ids.erase(it);
  }
};
