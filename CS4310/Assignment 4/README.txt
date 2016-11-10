Date:		10/10/2016
Class:		CS4310
Assignment:	Assignment 4
Author(s):	Alex Dekau

How to run:	python assgn4.py

Notes:
-------------------------------------------------------------------------------------------
I implemented the heap as a max heap because I wanted it to come out with the maximum value
first. This is because the greedy method picks the highest value when picking which item to
use. Since heapq doesn't allow for a max heap in the documentation, I implemented it with a
min heap using negative values to simulate a max heap by inverting the numbers when popped.

References:
-------------------------------------------------------------------------------------------
https://docs.python.org/2.7/library/heapq.html
