from MyVertex import MyVertex
from MyEdge import MyEdge

class MyGraph:
	counter = 0 

	def __init__(self, label=None):
		self.label = label
		self.uid = MyGraph.counter 
		MyGraph.counter = MyGraph.counter + 1

                # Initialize the sets V, E
                self.V = {}
                self.E = {}

	def getUid(self):
		return self.uid

	def getLabel(self):
		return self.label

        def new_vertex(self, label=None, value=None):
        	vert = MyVertex(label, value)
		self.V[vert.getUid()] = vert

	def new_edge(self, uid1, uid2, directed=False, label=None, value=None):
		edge = MyEdge(label, value, directed)
		edge.setVertex1(uid1)
		edge.setVertex2(uid2)

		if uid2 not in self.V[uid1].aV and uid1 is not uid2:
			self.V[uid1].add_adjacent_vertex(self.V[uid2])
			self.V[uid2].add_adjacent_vertex(self.V[uid1])

		if directed is not True:
			self.V[uid1].add_incoming_edge(edge)
			self.V[uid1].add_outgoing_edge(edge)
			self.V[uid2].add_incoming_edge(edge)
			self.V[uid2].add_outgoing_edge(edge)
		else:
			self.V[uid1].add_outgoing_edge(edge)
			self.V[uid2].add_incoming_edge(edge)

		# If its an edge looping to itself, dont increment twice.
		if uid1 is uid2:
			self.V[uid1].add_incident_edge(edge)
		else:
			self.V[uid1].add_incident_edge(edge)
			self.V[uid2].add_incident_edge(edge)
		self.E[edge.getUid()] = edge

	def remove_vertex(self, uid):
		tmp = self.V[uid]
		del self.V[uid]

		# It still exists despite being removed from the vector.
		for key, val in tmp.E.iteritems():
			del tmp.E[key].vleft
			del tmp.E[key].vright
			del tmp.E[key]

		#TODO: This needs to be refactored. Need to remove all references to this vertex. (From all edges that connect to it..)

	def num_vertices(self):
		return len(self.V)

	def num_edges(self):
		return len(self.E)

	def list_vertices(self):
		ret = []
		for i, e in self.V.iteritems():
			ret.append(e)

		return ret
	
	def list_edges(self):
		ret = []
		for i, e in self.E.iteritems():
			ret.append(e)

		return ret

	def vertex(self, uid):
		return self.V[uid]

	def edge(self, uid):
		return self.E[uid]

	def deg_vertex(self, uid):
		return len(self.V[uid].iedges)

	def incident_edges(self, uid):
		return self.V[uid].iedges

	def adjacent_edges(self, uid):
		return self.V[uid].get_adjacent()
	
	def end_vertices(self, uid):
		return [self.E[uid].v1, self.E[uid].v2]

	def are_adjacent(self, uid1, uid2):
		return uid2 in self.V[uid1].aV
