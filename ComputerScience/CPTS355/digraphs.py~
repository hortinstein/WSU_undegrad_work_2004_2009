#	Assignment 1 - Fun with Python
#	histo.py - Performs a count of the different digraphs
#	9/5/2007	
#	Alex Hortin

def digraphs(s): 
	print 'Counting Digraphs in' + s
	# This dictionary stores the occurances.
	occur = {} 
	list_di = []
	for i in range(len(s)-1):
		list_di.append(s[i] + s[i+1])
	
	# Going through the alphabet and counting each digraph's occurences, and storing this in the dictionary.
	for a in list_di:
		occur[a] = s.count(a)
	
	result = []
	for key, value in occur.items():
		result.append((value, '/' + key + '/'))
	result.sort()
	result.reverse()
	return result
