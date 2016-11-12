Date: 11/11/2016
Class: CS4310
Assignment: Assignment 7
Author(s): Alex Dekau

How to Run:
	make tester
	-OR-
	python tester.py

Notes:
	The data structure I ended up using makes use of Python dictionaries
	to provide a hashtable like structure to store the vertices and edges.
	This provides about an O(1.5) lookup time based on a given UID.
	Incoming and outgoing edges are stored in the MyVertex class as well
	as a list of incident edges and adjacent vertices.
	The MyEdge class stores the two vertices connected as well as if it is
	directed or not. To determine direction, it assumes V1 -> V2.
	Everything is calculated when an edge is added. There is no looping
	in this method.
	There is, however, looping when removing an edge or a vertex because
	some things need to be recalculated (like adjacent vertices).
	I do not return 0 for in_degree() if all edges are non-directed
	because I figured that if an edge is non directed then it is both
	part of the in_degree and the out_degree.

References:
	[1] http://stackoverflow.com/questions/13840379/python-multiply-all-items-in-a-list-together 
	[2] http://stackoverflow.com/questions/1679384/converting-python-dictionary-to-list
	[3] http://stackoverflow.com/questions/126524/iterate-a-list-with-indexes-in-python
	[4] http://stackoverflow.com/questions/1602934/check-if-a-given-key-already-exists-in-a-dictionary
	[5] http://stackoverflow.com/questions/3294889/iterating-over-dictionaries-using-for-loops-in-python
