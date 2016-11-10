class MyEdge:
	counter = 0 

	def __init__(self, label=None, value=None, directed=0):
		self.label = label
		self.value = value
		self.directed = directed
		self.uid = MyEdge.counter 
		MyEdge.counter = MyEdge.counter + 1

	def getUid(self):
		return self.uid

	def getLabel(self):
		return self.label

	def getValue(self):
		return self.value

	def is_directed(self):
		return self.directed == 1
