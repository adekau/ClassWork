class MyGraph:
	counter = 0 

	def __init__(self):
		self.uid = MyGraph.counter 
		MyGraph.counter = MyGraph.counter + 1
	def getUid(self):
		return self.uid
