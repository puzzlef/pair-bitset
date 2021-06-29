#pragma once
#include "_main.hxx"
#include "BitsetMonolithic.hxx"
#include "BitsetSubrange16.hxx"




template <class T=NONE>
class BitsetSwitched {
  BitsetMonolithic<T> mono;
  BitsetSubrange16<T> subr;
  int switchPoint;

  public:
  BitsetSwitched(int switchPoint) :
  switchPoint(switchPoint) {}

  // Which mode?
  bool isMonolithic() const { return subr.size() == 0; }
  bool isSubrange16() const { return !isMonolithic(); }

  void useMonolithic() {
    if (isMonolithic()) return;
    mono.clear();
    for (const auto& [id, v] : subr.entries())
      mono.add(id, v);
    subr.clear();
  }

  void useSubrange16() {
    if (isSubrange16()) return;
    subr.clear();
    for (const auto& [id, v] : mono.entries())
      subr.add(id, v);
    mono.clear();
  }


  // Read as iterable.
  public:
  auto entries() const { return ternaryIter(isMonolithic(), mono.entries(), subr.entries()); }
  auto keys()    const { return ternaryIter(isMonolithic(), mono.keys(),    subr.keys()); }
  auto values()  const { return ternaryIter(isMonolithic(), mono.values(),  subr.values()); }

  // Read operations.
  public:
  size_t size()      const { return isMonolithic()? mono.size()  : subr.size(); }
  bool   has(int id) const { return isMonolithic()? mono.has(id) : subr.has(id); }
  T      get(int id) const { return isMonolithic()? mono.get(id) : subr.get(id); }

  // Write operations
  public:
  void clear() {
    mono.clear();
    subr.clear();
  }

  void set(int id, T v) {
    if (isMonolithic()) mono.set(id, v);
    else subr.set(id, v);
  }

  void add(int id, T v=T()) {
    if (isMonolithic() && size()>=switchPoint) useSubrange16();
    if (isMonolithic()) mono.add(id, v);
    else subr.add(id, v);
  }

  void remove(int id) {
    if (isSubrange16() && size()<switchPoint/2) useMonolithic();
    if (isMonolithic()) mono.remove(id);
    else subr.remove(id);
  }
};
