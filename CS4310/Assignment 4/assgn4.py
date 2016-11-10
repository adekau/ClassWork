from __future__ import division
import heapq

class Knapsack:
	def __init__(self):
		self.heap = []
		self.x = []
	def addItem(self, benefit, weight):
		self.heap.append((benefit, weight, len(self.heap) + 1))
	def pop(self):
		tmp = heapq.heappop(self.heap)
		return (tmp[0] * -1, tmp[1], tmp[2], tmp[3])
	def greedy(self, W):
		oldval = ()
		for x in range(0, len(self.heap)):
			oldval = self.heap[x]
			self.heap[x] = (((oldval[0] * -1) / oldval[1]), oldval[2], oldval[0], oldval[1])
		heapq.heapify(self.heap)
		w = 0
		while w < W and len(self.heap) > 0:
			choice = self.pop()
			a = min(choice[3], (W - w))
			self.x.append((a, choice))	
			w = w + a
	def printResult(self):
		if len(self.x) > 0:
			totalWeight = 0
			totalBenefit = 0
			print "Results\n-------------------------------------------------------------------"
			for i in range(0, len(self.x)):
				totalWeight = totalWeight + self.x[i][0]
				totalBenefit = totalBenefit + (self.x[i][1][0] * self.x[i][0])
				print str(self.x[i][0]) + str(" of item ") + str(self.x[i][1][1])
				print str("\t-> at value ") + str(self.x[i][1][0]) + str(" per amount, benefit equals: ") + str(self.x[i][1][0] * self.x[i][0])
				print str("\t-> used ") + str(self.x[i][0]) + str(" of available ") + str(self.x[i][1][3])
			print str("Knapsack Weight: ") + str(totalWeight) + str(" Knapsack Benefit: ") + str(totalBenefit)
			print "-------------------------------------------------------------------"
