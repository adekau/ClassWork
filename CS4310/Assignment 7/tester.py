#Date: 11/11/2016
#Class: CS4310
#Assignment: Assignment 7
#Author(s): Alex Dekau

from MyGraph import MyGraph

graph = MyGraph("Assignment 7")

HNL = graph.new_vertex("HNL")
LAX = graph.new_vertex("LAX")
SFO = graph.new_vertex("SFO")
ORD = graph.new_vertex("ORD")
DFW = graph.new_vertex("DFW")
LGA = graph.new_vertex("LGA")
PVD = graph.new_vertex("PVD")
MIA = graph.new_vertex("MIA")

HNL_LAX = graph.new_edge(HNL, LAX, value=2555)
LAX_SFO = graph.new_edge(LAX, SFO, value=337)
LAX_DFW = graph.new_edge(LAX, DFW, value=1233)
LAX_ORD = graph.new_edge(LAX, ORD, True, value=1743)
SFO_ORD = graph.new_edge(SFO, ORD, value=1843)
ORD_PVD = graph.new_edge(ORD, PVD, value=849)
ORD_DFW = graph.new_edge(ORD, DFW, value=802)
DFW_LGA = graph.new_edge(DFW, LGA, value=1387)
DFW_MIA = graph.new_edge(DFW, MIA, value=1120)
LGA_MIA = graph.new_edge(LGA, MIA, value=1099)
PVD_LGA = graph.new_edge(PVD, LGA, True, value=142)
PVD_MIA = graph.new_edge(PVD, MIA, value=1205)

print "Num vertices (should be 8)"
print graph.num_vertices()

print "\nNum edges (should be 12)"
print graph.num_edges()

print "\nVertices:"
print graph.list_vertices()

print "\nEdges:"
print graph.list_edges()

print "\nVertex test:"
print graph.vertex(graph.list_vertices()[0].getUid()).getLabel()

print "\nDegree vertices:"
for i, el in enumerate(graph.list_vertices()):
	print "Vertex " + str(el.getLabel()) + ": " + str(graph.deg_vertex(el.getUid()))

print "\nIncident Edges:"
for i, el in enumerate(graph.list_vertices()):
	print "Vertex " + str(el.getLabel()) + ": " + str(map(lambda x: x.getValue(), graph.incident_edges(el.getUid())))

print "\nAdjacent Vertices:"
for i, el in enumerate(graph.list_vertices()):
	print "Vertex " + str(el.getLabel()) + ": " + str(map(lambda x: x.getLabel(), graph.adjacent_vertices(el.getUid())))

print "\nEnd Vertices:"
for i, el in enumerate(graph.list_edges()):
	print "Edge " + str(el.getValue()) + ": " + str(map(lambda x: graph.vertex(x).getLabel(), graph.end_vertices(el.getUid())))

print "\nAre Adjacent?"
for i, el1 in enumerate(graph.list_vertices()):
	for j, el2 in enumerate(graph.list_vertices()):
		print "Vertices " + str(el1.getLabel()) + ", " + str(el2.getLabel()) + ": " + str(graph.are_adjacent(el1.getUid(), el2.getUid()))

print "\n\n DIRECTED GRAPH STUFF --------"
print "Directed?"
for i, el in enumerate(graph.list_edges()):
	print "Edge " + str(el.getValue()) + ": " + str(el.is_directed())

print "\nIn degree:"
for i, el in enumerate(graph.list_vertices()):
	print "Vertex " + str(el.getLabel()) + ": " + str(graph.in_degree(el.getUid()))

print "\nIncoming Edges:"
for i, el in enumerate(graph.list_vertices()):
	print "Vertex " + str(el.getLabel()) + ": " + str(map(lambda x: x.getValue(), graph.incoming_edges(el.getUid())))

print "\nOutgoing Edges:"
for i, el in enumerate(graph.list_vertices()):
	print "Vertex " + str(el.getLabel()) + ": " + str(map(lambda x: x.getValue(), graph.outgoing_edges(el.getUid())))

print "\nAdjacent Incoming:"
for i, el in enumerate(graph.list_vertices()):
	print "Vertex " + str(el.getLabel()) + ": " + str(map(lambda x: x.getLabel(), graph.adjacent_incoming(el.getUid())))

print "\nAdjacent Outgoing:"
for i, el in enumerate(graph.list_vertices()):
	print "Vertex " + str(el.getLabel()) + ": " + str(map(lambda x: x.getLabel(), graph.adjacent_outgoing(el.getUid())))


print "\nRemoving an edge."
graph.remove_edge(HNL_LAX)
print "Removed an edge."
print "\nNum Edges:"
print graph.num_edges()

print "\nDegree of LAX"
print graph.deg_vertex(LAX)

print "\nDegree of HNL"
print graph.deg_vertex(HNL)

print "\nRemoving a vertex"
graph.remove_vertex(HNL)
print "Removed a vertex"

print "\nList Vertices"
print map(lambda x: x.getLabel(), graph.list_vertices())
