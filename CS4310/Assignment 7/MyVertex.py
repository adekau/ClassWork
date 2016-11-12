#Date: 11/11/2016
#Class: CS4310
#Assignment: Assignment 7
#Author(s): Alex Dekau

class MyVertex:
	counter = 0 

	def __init__(self, label=None, value=None):
		self.label = label
		self.value = value
		self.uid = MyVertex.counter 
		self.degree = 0
		MyVertex.counter = MyVertex.counter + 1

		# Edges that belong to this vertex.
		self.Ei = {} # Incoming
		self.Eo = {} # Outgoing

		# Incident edges list
		self.iedges = []

		# Adjacent vertices
		self.aV = {}

	def getUid(self):
		return self.uid

	def getLabel(self):
		return self.label

	def getValue(self):
		return self.value

	def add_incoming_edge(self, edge):
		self.Ei[edge.getUid()] = edge

	def add_outgoing_edge(self, edge):
		self.Eo[edge.getUid()] = edge

	def remove_edge(self, edge):
		euid = edge.getUid()

		if euid in self.Ei:
			del self.Ei[edge.getUid()]

		if euid in self.Eo:
			del self.Eo[edge.getUid()]
		self.iedges.remove(edge)

	def add_incident_edge(self, edge):
		self.iedges.append(edge)

	def add_adjacent_vertex(self, vtx):
		self.aV[vtx.getUid()] = vtx

	def get_adjacent(self):
		return self.aV.values()

	def get_incoming(self):
		return self.Ei.values()

	def get_outgoing(self):
		return self.Eo.values()
