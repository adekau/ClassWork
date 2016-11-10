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

	def new_edge(self, uid1, uid2, directed=0, label=None, value=None):
		edge = MyEdge(label, value, directed)
		edge.setLeftVertex(uid1)
		edge.setRightVertex(uid2)
		self.V[uid1].add_edge(edge)
		self.V[uid2].add_edge(edge)
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
