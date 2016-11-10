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

	# todo: Add vertex parameters.
	def new_edge(self, uid1, uid2, directed=0, label=None, value=None):
		edge = MyEdge(label, value, directed)
		uid1.add_edge(edge)
		uid2.add_edge(edge)
		self.E[edge.getUid()] = edge
