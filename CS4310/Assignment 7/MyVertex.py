class MyVertex:
	counter = 0 

	def __init__(self):
		self.uid = MyVertex.counter 
		MyVertex.counter = MyVertex.counter + 1
	def getUid(self):
		return self.uid
