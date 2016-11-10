from MyVertex import MyVertex
from MyEdge import MyEdge
from MyGraph import MyGraph

edge = MyEdge("test", 10)
vertex = MyVertex("test_v")
graph = MyGraph("Graph 1")

print edge.getUid()
print edge.getLabel()
print edge.getValue()
print vertex.getUid()
print vertex.getLabel()
print vertex.getValue()
print graph.getUid()
print graph.getLabel()

edge = MyEdge()
vertex = MyVertex()
graph = MyGraph()

print edge.getUid()
print vertex.getUid()
print graph.getUid()
