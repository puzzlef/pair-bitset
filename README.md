Performance of using vector vs unordered_map for storing the edges.

This experiment was for comparing the performance between:
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

The input data used for this experiment is available at ["graphs"] (for small
ones), and the [SuiteSparse Matrix Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# Using graph /home/subhajit/data/min-1DeadEnd.mtx ...
# order: 5 size: 6 {} [00000.432 ms] readMtx(DiGraphVector)
# order: 5 size: 6 {} [00000.119 ms] readMtx(DiGraphUmap)
# order: 7 size: 8 {} [00000.003 ms] addRandomEdge(DiGraphVector)
# order: 7 size: 9 {} [00000.003 ms] addRandomEdge(DiGraphUmap)
#
# Using graph /home/subhajit/data/min-2SCC.mtx ...
# order: 8 size: 12 {} [00000.460 ms] readMtx(DiGraphVector)
# order: 8 size: 12 {} [00000.138 ms] readMtx(DiGraphUmap)
# order: 13 size: 18 {} [00000.006 ms] addRandomEdge(DiGraphVector)
# order: 11 size: 18 {} [00000.005 ms] addRandomEdge(DiGraphUmap)
#
# Using graph /home/subhajit/data/min-4SCC.mtx ...
# order: 21 size: 35 {} [00000.520 ms] readMtx(DiGraphVector)
# order: 21 size: 35 {} [00000.246 ms] readMtx(DiGraphUmap)
# order: 30 size: 51 {} [00000.015 ms] addRandomEdge(DiGraphVector)
# order: 29 size: 51 {} [00000.015 ms] addRandomEdge(DiGraphUmap)
#
# Using graph /home/subhajit/data/min-NvgraphEx.mtx ...
# order: 6 size: 10 {} [00000.427 ms] readMtx(DiGraphVector)
# order: 6 size: 10 {} [00000.130 ms] readMtx(DiGraphUmap)
# order: 8 size: 14 {} [00000.006 ms] addRandomEdge(DiGraphVector)
# order: 9 size: 15 {} [00000.006 ms] addRandomEdge(DiGraphUmap)
#
# Using graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {} [02352.459 ms] readMtx(DiGraphVector)
# order: 281903 size: 2312497 {} [02911.403 ms] readMtx(DiGraphUmap)
# order: 422244 size: 3468728 {} [00263.010 ms] addRandomEdge(DiGraphVector)
# order: 422296 size: 3468729 {} [00526.338 ms] addRandomEdge(DiGraphUmap)
#
# Using graph /home/subhajit/data/web-BerkStan.mtx ...
# order: 685230 size: 7600595 {} [07496.090 ms] readMtx(DiGraphVector)
# order: 685230 size: 7600595 {} [07919.313 ms] readMtx(DiGraphUmap)
# order: 1027626 size: 11400859 {} [01017.691 ms] addRandomEdge(DiGraphVector)
# order: 1027645 size: 11400867 {} [02109.573 ms] addRandomEdge(DiGraphUmap)
#
# Using graph /home/subhajit/data/web-Google.mtx ...
# order: 916428 size: 5105039 {} [05538.273 ms] readMtx(DiGraphVector)
# order: 916428 size: 5105039 {} [06596.368 ms] readMtx(DiGraphUmap)
# order: 1363659 size: 7657548 {} [00768.152 ms] addRandomEdge(DiGraphVector)
# order: 1363454 size: 7657552 {} [01382.199 ms] addRandomEdge(DiGraphUmap)
#
# Using graph /home/subhajit/data/web-NotreDame.mtx ...
# order: 325729 size: 1497134 {} [01371.460 ms] readMtx(DiGraphVector)
# order: 325729 size: 1497134 {} [01462.346 ms] readMtx(DiGraphUmap)
# order: 481065 size: 2245695 {} [00211.873 ms] addRandomEdge(DiGraphVector)
# order: 480941 size: 2245697 {} [00258.035 ms] addRandomEdge(DiGraphUmap)
# ...
```

<br>
<br>


## References

- [unordered_map: which one is faster find() or count()?](https://stackoverflow.com/a/14159799/1413259)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/YQJjUUO.jpg)](https://www.youtube.com/watch?v=jfZisFrXBn4)

["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
