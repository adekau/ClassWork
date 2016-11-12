#Date: 11/11/2016
#Class: CS4310
#Assignment: Assignment 7
#Author(s): Alex Dekau

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
graph.new_edge(0,2,True) #5

print "Memory Addresses"
print graph.list_vertices()

print "A Adjacency"
print graph.vertex(0).aV
print "B Adjacency"
print graph.vertex(1).aV
print "C Adjacency"
print graph.vertex(2).aV

print "\nDuplicate using function\n"

print "A Adjacency"
print graph.adjacent_vertices(0)
print "B Adjacency"
print graph.adjacent_vertices(1)
print "C Adjacency"
print graph.adjacent_vertices(2)

# End vertices
print "End vertices for 3"
print graph.end_vertices(3)

# is adjacent?
print "Are 2 and 1 adjacent? (should be true)"
print graph.are_adjacent(2, 1)
print "Are 2 and 2 adjacent? (should be false)"
print graph.are_adjacent(2, 2)
print "Are 1 and 2 adjacent? (should be true)"
print graph.are_adjacent(1, 2)
print "Are 0 and 2 adjacent? (should be true)"
print graph.are_adjacent(0, 2)

print "Adjacent incoming A"
print map(lambda x: x.getUid(),graph.adjacent_incoming(0))
print "Adjacent incoming B"
print map(lambda x: x.getUid(),graph.adjacent_incoming(1))
print "Adjacent incoming C"
print map(lambda x: x.getUid(),graph.adjacent_incoming(2))
print "Adjacent outgoing A"
print map(lambda x: x.getUid(),graph.adjacent_outgoing(0))
print "Adjacent outgoing B"
print map(lambda x: x.getUid(),graph.adjacent_outgoing(1))
print "Adjacent outgoing C"
print map(lambda x: x.getUid(),graph.adjacent_outgoing(2))


graph.remove_edge(5)

print "REMOVED EDGE\n\n"

print "A Adjacency"
print graph.vertex(0).aV
print "B Adjacency"
print graph.vertex(1).aV
print "C Adjacency"
print graph.vertex(2).aV

print "\nDuplicate using function\n"

print "A Adjacency"
print graph.adjacent_vertices(0)
print "B Adjacency"
print graph.adjacent_vertices(1)
print "C Adjacency"
print graph.adjacent_vertices(2)

# End vertices
print "End vertices for 3"
print graph.end_vertices(3)

# is adjacent?
print "Are 2 and 1 adjacent? (should be true)"
print graph.are_adjacent(2, 1)
print "Are 2 and 2 adjacent? (should be false)"
print graph.are_adjacent(2, 2)
print "Are 1 and 2 adjacent? (should be true)"
print graph.are_adjacent(1, 2)
print "Are 0 and 2 adjacent? (should be false)"
print graph.are_adjacent(0, 2)

print "Adjacent incoming A"
print map(lambda x: x.getUid(),graph.adjacent_incoming(0))
print "Adjacent incoming B"
print map(lambda x: x.getUid(),graph.adjacent_incoming(1))
print "Adjacent incoming C"
print map(lambda x: x.getUid(),graph.adjacent_incoming(2))
print "Adjacent outgoing A"
print map(lambda x: x.getUid(),graph.adjacent_outgoing(0))
print "Adjacent outgoing B"
print map(lambda x: x.getUid(),graph.adjacent_outgoing(1))
print "Adjacent outgoing C"
print map(lambda x: x.getUid(),graph.adjacent_outgoing(2))
