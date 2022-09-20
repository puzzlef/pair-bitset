# https://www.kaggle.com/wolfram77/puzzlef-bitset-test-ordered-unordered
import os
from IPython.display import FileLink
src="bitset-test-ordered-unordered"
out="{}.txt".format(src)
!printf "" > "$out"
display(FileLink(out))
!ulimit -s unlimited && echo ""

# Download program
!rm -rf $src
!git clone https://github.com/puzzlef/$src
!echo ""

# Run
!g++ -std=c++17 -O3 main.cxx
!stdbuf --output=L ./a.out 2>&1 | tee -a "$out"
