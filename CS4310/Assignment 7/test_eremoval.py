from MyGraph import MyGraph

graph = MyGraph()


# Verticies
graph.new_vertex("A") 	 #0
graph.new_vertex("B") 	 #1
graph.new_vertex("C") 	 #2

#Edges-Undirected
graph.new_edge(0,1)	 #0
graph.new_edge(0,1,True) #1
graph.new_edge(1,2)	 #2
graph.new_edge(2,1,True) #3
graph.new_edge(2,2)	 #4

print "Vertex A incoming"
print graph.V[0].Ei
print "Vertex A outgoing"
print graph.V[0].Eo
print "Vertex B incoming"
print graph.V[1].Ei
print "Vertex B outgoing"
print graph.V[1].Eo
print "Vertex C incoming"
print graph.V[2].Ei
print "Vertex C outgoing"
print graph.V[2].Eo

print "Degree A"
print graph.deg_vertex(0)

print "Degree B"
print graph.deg_vertex(1)

print "Degree C"
print graph.deg_vertex(2)

print "Vertices"
print graph.list_vertices()
print "Edges"
print graph.list_edges()

print "Incident Edges A"
print graph.incident_edges(0)
print "Incident Edges B"
print graph.incident_edges(1)
print "Incident Edges C"
print graph.incident_edges(2)


print "\n"
print graph.vertex(0).aV
print graph.vertex(1).aV

graph.remove_edge(0)

print "\nREMOVED EDGE\n"

print "Vertex A incoming"
print graph.V[0].Ei
print "Vertex A outgoing"
print graph.V[0].Eo
print "Vertex B incoming"
print graph.V[1].Ei
print "Vertex B outgoing"
print graph.V[1].Eo
print "Vertex C incoming"
print graph.V[2].Ei
print "Vertex C outgoing"
print graph.V[2].Eo

print "Degree A"
print graph.deg_vertex(0)

print "Degree B"
print graph.deg_vertex(1)

print "Degree C"
print graph.deg_vertex(2)

print "Vertices"
print graph.list_vertices()
print "Edges"
print graph.list_edges()

print "Incident Edges A"
print graph.incident_edges(0)
print "Incident Edges B"
print graph.incident_edges(1)
print "Incident Edges C"
print graph.incident_edges(2)
