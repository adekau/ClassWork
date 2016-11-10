# Date: 10/24/2016
# Class: CS4310
# Assignment: Assignment 6
# Author(s): Alex Dekau

def quicksort(S):
	if len(S) > 1:
		p = S[0]
		LEG = partition(S, p)
		return quicksort(LEG[0])+LEG[1]+quicksort(LEG[2])
	else:
		return S

def partition(S, p):
	L = [] # Less than sequence
	E = [] # Equal sequence
	G = [] # Greater than sequence
	for y in S:
		if y < p:
			L.append(y)
		elif y == p:
			E.append(y)
		else:
			G.append(y)
	return (L, E, G)
