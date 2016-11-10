class MyEdge:
	counter = 0 

	def __init__(self, label=None, value=None, directed=0):
		self.label 	= label
		self.value 	= value
		self.directed	= directed
		self.uid 	= MyEdge.counter 
		self.vleft 	= None
		self.vright 	= None
		MyEdge.counter 	= MyEdge.counter + 1

	def getUid(self):
		return self.uid

	def getLabel(self):
		return self.label

	def getValue(self):
		return self.value

	def is_directed(self):
		return self.directed == 1

	def getLeftVertex(self):
		return self.vleft
	
	def getRightVertex(self):
		return self.vright

	def setLeftVertex(self, vtx):
		self.vleft = vtx

	def setRightVertex(self, vtx):
		self.vright = vtx
