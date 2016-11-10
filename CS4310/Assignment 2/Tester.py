import DataStructures

print "TESTING: STACK\n----------"

testStack = DataStructures.Stack()
print "pushing 5"
testStack.push(5)
print "pushing 6"
testStack.push(6)
print "pushing 7"
testStack.push(7)
print testStack.pop()
print testStack.pop()
print "pushing 8"
testStack.push(8)
print testStack.pop()
print testStack.pop()

print "\nTESTING: QUEUE\n----------"
testQueue = DataStructures.Queue()
print "queueing 0"
testQueue.enqueue(0)
print "queueing 1"
testQueue.enqueue(1)
print "queueing 2"
testQueue.enqueue(2)
print testQueue.dequeue()
print "queueing 3"
testQueue.enqueue(3)
print testQueue.dequeue()
print testQueue.dequeue()
print testQueue.dequeue()

print "\nTESTING: LIST\n----------"
testList = DataStructures.List(10)
print "Adding B to spot 0"
testList.add(0, 'B')
print testList.theList
print "Adding C to spot 1"
testList.add(1, 'C')
print testList.theList
print "Adding A to spot 0"
testList.add(0, 'A')
print testList.theList
print "Getting spot 1"
print testList.get(1)
print "Setting spot 0 to 0"
testList.set(0, 0)
print testList.theList
print "Removing spot 1"
testList.remove(1)
print testList.theList
print "Getting spot 1"
print testList.get(1)
print "Getting spot 2"
print testList.get(2)
print "Setting spot 2 to 'D'"
testList.set(2, 'D')
print testList.theList
print "Adding D to spot 2"
testList.add(2, 'D')
print testList.theList
print "Setting spot 2 to 'C'"
testList.set(2, 'C')
print testList.theList
