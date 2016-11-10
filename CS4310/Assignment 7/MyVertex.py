class MyVertex:
	counter = 0 

	def __init__(self, label=None, value=None):
		self.label = label
		self.value = value
		self.uid = MyVertex.counter 
		MyVertex.counter = MyVertex.counter + 1

	def getUid(self):
		return self.uid

	def getLabel(self):
		return self.label

	def getValue(self):
		return self.value
