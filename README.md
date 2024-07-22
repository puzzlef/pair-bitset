Design of **bitset** for storing *key-value pairs*.

<br>


### With Unordered map

This experiment ([unordered-map]) was for comparing the performance between:
1. Storing `DiGraph` edges using **vector**.
2. Storing `DiGraph` edges using **unordered_map**.

Each approach was attempted with a number of different graphs, performing
2 graph structure operations, `readMtx` and `addRandomEdge`. Surprisingly,
**unordered_map** approach performs works in all cases compared to using
**vector** for edges. That possibly means that even though a *vector* needs
*O(n)* search time for checking existence of edge, it still tends to be faster
that *unordered_map*, especially since many vertices will have a small number
of edges, where a simple linear search is usually better. A hybrid approach
might yield better results.

[unordered-map]: https://github.com/puzzlef/pair-bitset/tree/unordered-map

<br>


### With Sorted vs Unsorted Vector

This experiment ([vector-sorted-vs-unsorted]) was for comparing performance between:
1. Read graph edges to **sorted bitset** based DiGraph & transpose.
2. Read graph edges to **unsorted bitset** based DiGraph & transpose.

Each approach was attempted on a number of temporal graphs, running each with
multiple batch sizes (`1`, `5`, `10`, `50`, ...). Each batch size was run 5
times for each approach to get a good time measure. **Transpose** of DiGraph
based on **sorted bitset** is clearly **faster** than the *unsorted* one.
However, with **reading graph edges** there is no clear winner (sometimes
*sorted* is *faster* especially for large graphs, and sometimes *unsorted*).
Maybe when new edges have many duplicates, **inserts are less**, and hence
sorted version is faster (since sorted bitset has slow insert time).

[vector-sorted-vs-unsorted]: https://github.com/puzzlef/pair-bitset/tree/vector-sorted-vs-unsorted

<br>


### Adjusting Unsorted size of Partially sorted Vector

The partially sorted bitset maintains 2 sublists in the same vector, **sorted**
and **unsorted**. New items are added to the *unsorted sublist* at the end.
When *unsorted sublist* grows beyond **limit**, it is merged with the *sorted*
*sublist* (*unsorted sublist* becomes empty). Lookup can be performed in either
the *sorted sublist* first, or the *unsorted* one.

This experiment ([vector-partially-sorted-adjust-unsorted]) was for comparing
performance of reading graph edges (`readSnapTemporal`) and transpose
(`transposeWithDegree`) between:
1. Merge sublists using **sort** (modes `0`, `1`).
2. Merge sublists **in-place** (modes `2`, `3`).
3. Merge sublists using **extra space for sorted sublist** (modes `4`, `5`).
4. Merge sublists using **extra space for unsorted sublist** (modes `6`, `7`).

In each case given above, **lookup** in bitset is done either in **sorted**
**sublist** first, or in **unsorted** sublist:
1. Lookup first in **sorted sublist** (modes `0`, `2`, `4`, `6`).
2. Lookup first in **unsorted sublist** (modes `1`, `3`, `5`, `7`).

For all of the total `8` modes above, *unsorted* **limit** for **unsorted sublist**
was adjusted with multiple sizes (`1`, `2`, `3`, ..., `10`, `20`, ..., `10000`).
Merge using **sort** simply sorts the entire list. Merging **in-place** uses
`std::inplace_merge()`. Merge using **extra space for sorted sublist**
uses a shared temporary buffer for storing sorted values (which could be large)
and then performs a `std::merge()` after sorting the *unsorted sublist*. On the
other hand, merge using **extra space for unsorted sublist** uses a shared
temporary buffer for storing unsorted values (which is potentially much smaller
than the sorted sublist), and performs a *reverse merge* after sorting the
*unsorted sublist*. From the result it appears that merging sublists **in-place**,
and using **extra space for unsorted sublist**, both with first lookup in
**sorted sublist** are **fast** (modes `inplace-s`=`2`, `extrau-s`=`6`). For both
cases, a **limit** of `128` appears to be a good choice.

[vector-partially-sorted-adjust-unsorted]: https://github.com/puzzlef/pair-bitset/tree/vector-partially-sorted-adjust-unsorted

<br>


### With Fully vs Partially sorted Vector

This experiment ([vector-sorted-full-vs-partial]) was for comparing performance between:
1. Read graph edges to **sorted bitset** based DiGraph & transpose.
2. Read graph edges to **partially sorted bitset** based DiGraph & transpose.

Each approach was attempted on a number of temporal graphs, running each 5
times to get a good time measure. **Transpose** of DiGraph based on **sorted**
**bitset** is clearly **faster** than the *partially sorted* one. This is
possibly because *partially sorted* bitset based DiGraph causes higher cache
misses due to random accesses (while reversing edges). However, with
**reading graph edges** there is no clear winner (sometimes *partially sorted*
is *faster* especially for large graphs, and sometimes *unsorted*). On average,
it is better to stick with simple **fully sorted** bitset.

[vector-sorted-full-vs-partial]: https://github.com/puzzlef/pair-bitset/tree/vector-sorted-full-vs-partial

<br>


### Adjusting In-built buffer of Vector

This experiment ([vector-adjust-inbuilt-buffer]) is for comparing various
**buffer sizes** for BitSet with **small vector optimization**. **Read graph**
**edges**, and **transpose**,  was attempted on a number of temporal graphs,
running each with multiple buffer sizes (`1`, `2`, `4`, ...`4096`). Each buffer
size was run 5 times for for both **read** and **transpose** to get a good time
measure.

On average, a **buffer size** of `4` seems to give **small** **improvement**.
Any further increase in buffer size slows down performance. This is possibly
because of unnecessaryily large contiguous large memory allocation needed by the
buffer, and low cache-hit percent due to widely separated edge data (due to the
static buffer). In fact it even crashes when 26 instances of graphs with varying
buffer sizes can't all be held in memory. Hence, **small vector**
**optimization** is **not useful**, atleast when used for graphs.

[vector-adjust-inbuilt-buffer]: https://github.com/puzzlef/pair-bitset/tree/vector-adjust-inbuilt-buffer

<br>


### With Sorted vs Unsorted 16-bit Subranged Vector

This experiment ([vector-subrange16-sorted-vs-unsorted]) is for comparing
**sorted** vs **unsorted** for *16-bit subrange* based BitSet. Each approach was
attempted on a number of temporal graphs, running each with multiple read sizes
(`1E+3`, `5E+3`, `1E+4`, `5E+4`, ...). Each read size was run 5 times for each
approach to get a good time measure. **16-bit subrange** **bitset** is similar
to [Roaring bitmap], which also breaks up all integers into buckets of 2^16
integers.

Although both sorted and unsorted 16-bit subrange based bitsets perform
similarly, on average **unsorted** approach performs **slightly better** than
sorted approach.

[vector-subrange16-sorted-vs-unsorted]: https://github.com/puzzlef/pair-bitset/tree/vector-subrange16-sorted-vs-unsorted

<br>


### Other experiments

- [vector-batched-sorted-vs-unsorted](https://github.com/puzzlef/pair-bitset/tree/vector-batched-sorted-vs-unsorted)
- [vector-subrange16-adjust-switch-point](https://github.com/puzzlef/pair-bitset/tree/vector-subrange16-adjust-switch-point)

<br>
<br>


## References

- [Fast Compact Sparse Bit Sets by Justin Collins](https://blog.presidentbeef.com/blog/2013/09/02/fast-compact-sparse-bitsets/)
- [SparseBitSet: An efficient sparse bit set implementation for Java; by Brett Wooldridge](https://github.com/brettwooldridge/SparseBitSet)
- [boost::dynamic_bitset<Block, Allocator>](https://www.boost.org/doc/libs/1_36_0/libs/dynamic_bitset/dynamic_bitset.html)
- [Stanford Large Network Dataset Collection](http://snap.stanford.edu/data/index.html)
- [Good library for bitsets or bitarrays](https://stackoverflow.com/questions/4052795/good-library-for-bitsets-or-bitarrays)

<br>
<br>


[![](https://i.imgur.com/DuJu78s.jpg)](https://www.youtube.com/watch?v=2k_ihEEZG-o)


[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
