class MyEdge:
	counter = 0 

	def __init__(self):
		self.uid = MyEdge.counter 
		MyEdge.counter = MyEdge.counter + 1
	def getUid(self):
		return self.uid
