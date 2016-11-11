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

print "A Adjacency"
print graph.vertex(0).aV
print "B Adjacency"
print graph.vertex(1).aV
print "C Adjacency"
print graph.vertex(2).aV

print "\nDuplicate using function\n"

print "A Adjacency"
print graph.adjacent_edges(0)
print "B Adjacency"
print graph.adjacent_edges(1)
print "C Adjacency"
print graph.adjacent_edges(2)
