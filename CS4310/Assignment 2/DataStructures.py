# Date: 9/15/2016
# Class: CS 4310
# Assignment: Assignment 2
# Author(s): Alex Dekau

class Stack:
	def __init__(self):
		self.n = 100
		self.theStack = [None] * self.n
		self.t = -1
	
	def push(self, o):
		if self.t + 1 == self.n:
			# if the array is out of space, double it and try again
			self.theStack.extend([None] * self.n)
			self.n = self.n * 2
			self.push(o)
		else:
			self.t = self.t + 1 
			self.theStack[self.t] = o
			return

	def pop(self):
		if self.isEmpty():
			return None
		else:
			self.t = self.t - 1
			return self.theStack[self.t + 1]

	def isEmpty(self):
		return (self.t) < 0

	def size(self):
		return self.t + 1

	def top(self):
		return self.theStack[self.t]

class Queue:
	def __init__(self):
		self.N = 100
		self.theQueue = [None] * self.N
		self.f = 0
		self.sz = 0
		self.r = None

	def size(self):
		return self.sz

	def isEmpty(self):
		return (self.sz == 0)

	def enqueue(self, o):
		if self.size() == (self.N - 1):
			# if the size limit is reached, add more storage space then try again.
			self.theQueue.extend([None] * self.N)
			self.N = self.N * 2
			self.enqueue(o)
		else:
			self.r = (self.f + self.sz) % self.N 
			self.theQueue[self.r] = o
			self.sz = (self.sz + 1)

	def dequeue(self):
		if self.isEmpty():
			return None
		else:
			o = self.theQueue[self.f]
			self.f = (self.f + 1) % self.N
			self.sz = (self.sz - 1)
			return o

	def first(self):
		return self.theQueue[self.f] 

class List:
	def __init__(self, size):
		self.N = size
		self.theList = [None] * self.N
		self.n = 0

	def add(self, r, e):
		if self.n == self.N:
			# if the size limit is reached, then add more storage space and try again.
			self.theList.extend([None] * self.N)
			self.N = self.N * 2
			self.add(r, e)
		if r < self.n:
			#looks like I'm going to have to do the loop a bit different
			#since python doesn't seem to let you do c style loops
			for i in range(1, (self.n - r) + 1):
				index = self.n - i
				self.theList[index + 1] = self.theList[index]
		self.theList[r] = e
		self.n = self.n + 1

	def remove(self, r):
		#e as a temp variable
		e = self.theList[r]		
		if r < self.n - 1:
			#same thing as above, have to change the loop structure a bit
			#to work in python. (as far as I'm aware)
			for i in range(0, abs(r - (self.n - 2)) + 1):
				index = r + i
				self.theList[index] = self.theList[index + 1]
		self.n = self.n - 1
		return e

	def get(self, r):
		# check if it's in the list.
		if r < self.n:
			return self.theList[r]
		else:
			return None


	def set(self, r, e):
		if self.get(r) is not None:
			self.theList[r] = e
		else:
			print "error"

