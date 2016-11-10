from random import randrange

def inPlaceQuickSort(S, a, b):
	if a >= b:
		return
	l = inPlacePartition(S, a, b)
	print "L is: " + str(l)
	inPlaceQuickSort(S, a, l - 1)
	inPlaceQuickSort(S, l + 1, b)

def inPlacePartition(S, a, b):
	print "Doing in place for " + str(a) + "," + str(b)
	R = randrange(a, b + 1)
	# Now swap the elements.
	tmp = S[R]
	S[R] = S[b]
	S[b] = tmp
	p = S[b]
	l = a
	r = b - 1
	while l <= r:
		print "Doing left."
		while l <= r and S[l] <= p:
			print str(S[l]) + " <= " + str(p)
			l = l + 1
			print "New L: " + str(l)
		print "Doing right."
		while r >= l and S[r] >= p:
			print str(S[r]) + ">= " + str(p)
			r = r - 1
			print "New R: " + str(r)
		if l < r:
			print "L < R. Swapping"
			tmp = S[l]
			S[l] = S[r]
			S[r] = tmp
	print "L no longer <= r. Swapping l and b"
	tmp = S[l]
	S[l] = S[b]
	S[b] = tmp
	return l

arr = [5,12,1,2,3]
print "Start array: " + str(arr)
inPlaceQuickSort(arr, 0, 4)

print "Sorted array: " + str(arr)
