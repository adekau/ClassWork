class MyVertex:
	counter = 0 

	def __init__(self, label=None, value=None):
		self.label = label
		self.value = value
		self.uid = MyVertex.counter 
		MyVertex.counter = MyVertex.counter + 1

		# Edges that belong to this vertex.
		self.E = {}

	def getUid(self):
		return self.uid

	def getLabel(self):
		return self.label

	def getValue(self):
		return self.value

	def add_edge(self, edge):
		self.E[edge.getUid()] = edge

	def remove_edge(self, edge):
		del self.E[edge.getUid()]
