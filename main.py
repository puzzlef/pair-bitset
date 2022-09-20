# https://www.kaggle.com/wolfram77/puzzlef-bitset-batched-sorted-vs-unsorted
import os
from IPython.display import FileLink
src="bitset-batched-sorted-vs-unsorted"
inp="/kaggle/input/graphs-temporal"
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
!stdbuf --output=L ./a.out $inp/CollegeMsg.txt             2>&1 | tee -a "$out"
!stdbuf --output=L ./a.out $inp/email-Eu-core-temporal.txt 2>&1 | tee -a "$out"
!stdbuf --output=L ./a.out $inp/sx-mathoverflow.txt        2>&1 | tee -a "$out"
!stdbuf --output=L ./a.out $inp/sx-askubuntu.txt           2>&1 | tee -a "$out"
!stdbuf --output=L ./a.out $inp/sx-superuser.txt           2>&1 | tee -a "$out"
!stdbuf --output=L ./a.out $inp/sx-stackoverflow.txt       2>&1 | tee -a "$out"
!stdbuf --output=L ./a.out $inp/wiki-talk-temporal.txt     2>&1 | tee -a "$out"
