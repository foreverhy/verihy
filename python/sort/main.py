import sys

from Sort import MergeSort

a = []
for line in sys.stdin:
    a.append(int(line.strip()))

MergeSort.sort(a, 0, len(a))

for i in a:
    print i




