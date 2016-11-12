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

print "Is 1 directed? (true)"
print graph.is_directed(1)
print "Is 2 directed? (false)"
print graph.is_directed(2)

print "In degree A (1)"
print graph.in_degree(0)
print "In degree B (4)"
print graph.in_degree(1)
print "In degree C (2)"
print graph.in_degree(2)
print "Out degree A (2)"
print graph.out_degree(0)
print "Out degree B (2)"
print graph.out_degree(1)
print "Out degree C (3)"
print graph.out_degree(2)
