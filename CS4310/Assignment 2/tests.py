from DataStructures import *

print "Stack:"
s = Stack()
print s.pop()
print s.top()
print s.size()
print s.isEmpty()
print s.push(5)
print s.push(3)
print s.top()
print s.size()
print s.push(4)
print s.isEmpty()
print s.pop()
print s.pop()
print s.pop()

print "\n\nQueue:"
q = Queue()
print q.dequeue()
print q.isEmpty()
print q.first()
print q.size()
print q.enqueue(3)
print q.enqueue(5)
print q.isEmpty()
print q.first()
print q.size()
print q.dequeue()
print q.dequeue()
print q.dequeue()

print "\n\nList:"
l = List(7)
print l.add(0, 'A')
print l.add(0, 'B')
print l.get(1)
print l.set(2, 'C')
print l.add(2, 'C')
print l.add(4, 'D')
print l.theList
print "get " + str(l.get(4))
print l.remove(1)
print l.get(3)

