# Date: 10/24/2016
# Class: CS4310
# Assignment: Assignment 6
# Author(s): Alex Dekau

def mergesort(S):
	if len(S) < 2:
		return S[:]
	else:
		mid = len(S) // 2 # // is integer divide.
		l = mergesort(S[:mid])
		r = mergesort(S[mid:])
		return merge(l, r)

def merge(s1, s2):
	result = []
	i = 0
	j = 0
	n1 = len(s1)
	n2 = len(s2)
	while i < n1 and j < n2:
		if s1[i] < s2[j]:
			result.append(s1[i])
			i = i + 1
		else:
			result.append(s2[j])
			j = j + 1
	while i < n1:
		result.append(s1[i])
		i = i + 1
	while j < n2:
		result.append(s2[j])
		j = j + 1
	return result
