#from __future__ import division
from heapq import heappush, heappop

class Greedy(object):
	items = []
	
	def addItem(self, benefit, weight):
		x = 0
		v = 0
		z = len(self.items) + 1
		item = [-benefit, weight, x, v, z]
		heappush(self.items, item)

	def greedy(self, W):
		w = 0
		for i in range(len(self.items)):
			self.items[i][2] = 0
			self.items[i][3] = -self.items[i][0] / self.items[i][1]
		while w < W and len(self.items) > 0:
			item = heappop(self.items)
			a = min(item[1], W - w)
			item[2] = a
			w = w + a
			print "Taking " + str(a) + " of item " + str(item[4])



gr = Greedy()
gr.addItem(12, 4)
gr.addItem(32, 8)
gr.addItem(40, 2)
gr.addItem(30, 6)
gr.addItem(50, 1)
print gr.items
gr.greedy(10)

