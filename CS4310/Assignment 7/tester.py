from MyVertex import MyVertex
from MyEdge import MyEdge
from MyGraph import MyGraph

graph = MyGraph("Graph 1")


graph.new_vertex()
graph.new_vertex()

graph.new_edge(0, 1)

print graph.V[0].E[0].is_directed()
print graph.V[0].E
print graph.V[1].E
