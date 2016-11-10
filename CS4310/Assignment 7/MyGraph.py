class MyGraph:
	counter = 0 

	def __init__(self, label=None):
		self.label = label
		self.uid = MyGraph.counter 
		MyGraph.counter = MyGraph.counter + 1

		# Initialize the adjacency matrix.
		

	def getUid(self):
		return self.uid

	def getLabel(self):
		return self.label
