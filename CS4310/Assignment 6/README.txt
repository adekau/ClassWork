Date: 10/24/2016
Class: CS4310
Assignment: Assignment 6
Author(s): Alex Dekau

How to run:
python tester.py

Notes:
This assignment was a little bit more difficult to follow the algorithms
in the slides and the books.

For mergesort there was no mergesort algorithm in the book. Only an algorithm
for the merge part of it. The ones given in the slides would be impossible to
implement as given due to the fact that the method definitions do not match
up. For example, it was 'merge(s1, s2, S)', then in the mergeSort algorithm
above it would call merge like so: 'S <- merge(s1, s2)'. The arguments do not
match up and if you were to change them to match up, then it doesn't make
sense to assign to S the result because the algorithm for merge does not
return anything. So I had to change quite a bit for this one to work...

For quicksort, there was nothing whatsoever in the book as far as an algorithm.
I had to get the algorithm from your slides, and that one didn't work
as expected in python, so I had to change the loop structure a bit.

References:
http://stackoverflow.com/questions/18761766/mergesort-python
http://stackoverflow.com/questions/18262306/quick-sort-with-python
