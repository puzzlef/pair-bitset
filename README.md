Testing the effectiveness of **sorted** vs **unsorted** list of integers for BitSet.

This experiment was for comparing performance between:
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
# order: 4930 size: 124645 {} [00257.604 ms] readSnapTemporal [sorted]
# order: 4930 size: 124645 {} [00251.746 ms] readSnapTemporal [unsorted]
# order: 4930 size: 124645 {} [00002.452 ms] transposeWithDegree [sorted]
# order: 4930 size: 124645 {} [00003.188 ms] transposeWithDegree [unsorted]
#
# Using graph /home/subhajit/data/CollegeMsg.txt ...
# Temporal edges: 59836
# order: 9495 size: 101480 {} [00051.542 ms] readSnapTemporal [sorted]
# order: 9495 size: 101480 {} [00048.538 ms] readSnapTemporal [unsorted]
# order: 9495 size: 101480 {} [00001.948 ms] transposeWithDegree [sorted]
# order: 9495 size: 101480 {} [00002.423 ms] transposeWithDegree [unsorted]
#
# Using graph /home/subhajit/data/sx-mathoverflow.txt ...
# Temporal edges: 506551
# order: 124090 size: 1199890 {} [00454.674 ms] readSnapTemporal [sorted]
# order: 124090 size: 1199890 {} [00465.244 ms] readSnapTemporal [unsorted]
# order: 124090 size: 1199890 {} [00034.506 ms] transposeWithDegree [sorted]
# order: 124090 size: 1199890 {} [00060.384 ms] transposeWithDegree [unsorted]
#
# Using graph /home/subhajit/data/sx-askubuntu.txt ...
# Temporal edges: 964438
# order: 796580 size: 2984665 {} [00910.169 ms] readSnapTemporal [sorted]
# order: 796580 size: 2984665 {} [00957.065 ms] readSnapTemporal [unsorted]
# order: 796580 size: 2984665 {} [00107.902 ms] transposeWithDegree [sorted]
# order: 796580 size: 2984665 {} [00209.675 ms] transposeWithDegree [unsorted]
#
# Using graph /home/subhajit/data/sx-superuser.txt ...
# Temporal edges: 1443340
# order: 970425 size: 4624430 {} [01375.067 ms] readSnapTemporal [sorted]
# order: 970425 size: 4624430 {} [01594.650 ms] readSnapTemporal [unsorted]
# order: 970425 size: 4624430 {} [00167.261 ms] transposeWithDegree [sorted]
# order: 970425 size: 4624430 {} [00429.451 ms] transposeWithDegree [unsorted]
#
# Using graph /home/subhajit/data/wiki-talk-temporal.txt ...
# Temporal edges: 7833141
# order: 5700745 size: 16547960 {} [07438.125 ms] readSnapTemporal [sorted]
# order: 5700745 size: 16547960 {} [21607.051 ms] readSnapTemporal [unsorted]
# order: 5700745 size: 16547960 {} [00718.922 ms] transposeWithDegree [sorted]
# order: 5700745 size: 16547960 {} [12030.658 ms] transposeWithDegree [unsorted]
#
# Using graph /home/subhajit/data/sx-stackoverflow.txt ...
# Temporal edges: 63497051
# order: 13009885 size: 181167250 {} [76439.016 ms] readSnapTemporal [sorted]
# order: 13009885 size: 181167250 {} [94455.875 ms] readSnapTemporal [unsorted]
# order: 13009885 size: 181167250 {} [10782.336 ms] transposeWithDegree [sorted]
# order: 13009885 size: 181167250 {} [34569.242 ms] transposeWithDegree [unsorted]
```

[![](https://i.imgur.com/2nTygZh.png)][sheets]
[![](https://i.imgur.com/yb4YZYM.png)][sheets]
[![](https://i.imgur.com/tgXdyoR.png)][sheets]
[![](https://i.imgur.com/mpYCYWV.png)][sheets]

<br>
<br>


## References

- [Stanford Large Network Dataset Collection]

<br>
<br>

[![](https://i.imgur.com/DuJu78s.jpg)](https://www.youtube.com/watch?v=2k_ihEEZG-o)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
[charts]: https://photos.app.goo.gl/c2ivFPbEXdw6ZFaM7
[sheets]: https://docs.google.com/spreadsheets/d/1AB23nO5K71-TWe7aY6cf5Rte7jfLhfITPFBnRB_jVzM/edit?usp=sharing
