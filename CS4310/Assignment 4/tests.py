from assgn4 import *

def test_case(b, w, W, case):
	print "Test case " + str(case) + ":"
	knapsack = Knapsack()
	for i, val in enumerate(b):
		knapsack.addItem(b[i], w[i])
	knapsack.greedy(W)
	knapsack.printResult()
	print "\n\n"

#Case 1:
test_case([8,3,4,2,4,15,10], [4,1,1,2,8,5,5], 20, 1)
#Case 2:
test_case([12,32,40,30,50], [4,8,2,6,1], 10, 2)
#Case 3:
test_case([30,5,2], [15,10,10], 10, 3)
#Case 4:
test_case([30,5,2], [15,10,10], 50, 4)
