# Date: 10/18/2016
# Class: CS4310
# Assignment: Assignment 5
# Author(s): Alex Dekau

def lcs(X, Y):
	arr = [[0 for j in range(len(Y) + 1)] for i in range(len(X) + 1)]

	# These loops are redundant from initializing the array with 0s.
	# Leaving them in for the sake of having the algorithm correct.
	for (i, unused) in enumerate(X):
		arr[i][0] = 0

	for (j, unused) in enumerate(Y):
		arr[0][j] = 0

	for (i, unused) in enumerate(X):
		for (j, unused) in enumerate(Y):
			if X[i] == Y[j]:
				arr[i + 1][j + 1] = arr[i][j] + 1
			else:
				arr[i + 1][j + 1] = max(arr[i][j + 1], arr[i + 1][j])
	return arr

def reverse_lcs(X, Y, arr):
	idxI = len(X)
	idxJ = len(Y)
	ret = ""

	while (idxI > 0 and idxJ > 0):
		if X[idxI - 1] == Y[idxJ - 1]:
			ret += str(X[idxI - 1])
			idxI = idxI - 1
			idxJ = idxJ - 1
		else:
			if arr[idxI - 1][idxJ] > arr[idxI][idxJ - 1]:
				idxI = idxI - 1
			elif arr[idxI - 1][idxJ] == arr[idxI][idxJ - 1]:
				if len(X) > len(Y):
					idxI = idxI - 1
				elif len(Y) > len(X):
					idxJ = idxJ - 1
				else:
					idxI = idxI - 1
			else:
				idxJ = idxJ - 1
	return ret[::-1]
