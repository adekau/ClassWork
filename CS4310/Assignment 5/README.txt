Date: 10/18/2016
Class: CS4310
Assignment: Assignment 5
Author(s): Alex Dekau

How to Run:
------------------------
python lcs.py		
-OR-
python2 lcs.py

Notes:	
------------------------
Since I can't do -1 indexed arrays, I had to do it from 0 to length + 1. 
Also, since I found a way to 0 index the 2-dimensional array in python easily[1], the two for loops at the beginning
are technically not needed. I put them in there just so the code is as close to the algorithm as possible.
Any case of i or j became i + 1 or j + 1 respectively.

The algorithm for reversing the process and getting the longest subsequence was an algorithm that I formed
from the green worksheet handed out in class. 

The weird "return ret[::-1]" thing at the end reverses the string [3].

References:
------------------------
[1]  http://stackoverflow.com/questions/2397141/how-to-initialize-a-two-dimensional-array-in-python
[2]  http://stackoverflow.com/questions/8848294/how-to-get-char-from-string-by-index
[3]  http://stackoverflow.com/questions/931092/reverse-a-string-in-python
