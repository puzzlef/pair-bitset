Performance of **fully sorted** vs **partially sorted** BitSet ([inplace-s128]).

This experiment was for comparing performance between:
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

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at the
[Stanford Large Network Dataset Collection]. This experiment was done with
guidance from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/email-Eu-core-temporal.txt
$ ./a.out ~/data/CollegeMsg.txt
$ ...

# Using graph /home/subhajit/data/email-Eu-core-temporal.txt ...
# Temporal edges: 332335
# order: 986 size: 24929 {} [00274.367 ms] readSnapTemporal [full]
# order: 986 size: 24929 {} [00269.612 ms] readSnapTemporal [partial]
# order: 986 size: 24929 {} [00002.632 ms] transposeWithDegree [full]
# order: 986 size: 24929 {} [00002.873 ms] transposeWithDegree [partial]
#
# ...
#
# Using graph /home/subhajit/data/sx-stackoverflow.txt ...
# Temporal edges: 63497051
# order: 2601977 size: 36233450 {} [85708.555 ms] readSnapTemporal [full]
# order: 2601977 size: 36233450 {} [78818.172 ms] readSnapTemporal [partial]
# order: 2601977 size: 36233450 {} [11160.986 ms] transposeWithDegree [full]
# order: 2601977 size: 36233450 {} [14548.278 ms] transposeWithDegree [partial]
```

[![](https://i.imgur.com/guNANHM.png)][sheets]
[![](https://i.imgur.com/6aJFdjx.png)][sheets]
[![](https://i.imgur.com/UwP23lx.png)][sheets]
[![](https://i.imgur.com/f545BjP.png)][sheets]

<br>
<br>


## References

- [Stanford Large Network Dataset Collection]

<br>
<br>

[![](https://i.imgur.com/LRnibFS.jpg)](https://www.youtube.com/watch?v=AQA8zLrTMd8)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
[inplace-s128]: https://github.com/puzzlef/bitset-partially-sorted-adjust-unsorted
[charts]: https://photos.app.goo.gl/xHNk3DZk6LeicwgV6
[sheets]: https://docs.google.com/spreadsheets/d/1sG1clHwXsnbBmvrFM7JMVqbSGavzzsEMpockw0sK4J4/edit?usp=sharing
