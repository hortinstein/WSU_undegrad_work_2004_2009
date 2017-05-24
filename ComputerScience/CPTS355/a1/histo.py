#	Assignment 1 - Fun with Python
#	histo.py - Performs a count of all the letter frequencies in the given string
#	9/5/2007	
#	Alex Hortin

def histo(s): 
	print 'Counting occurances of letters in' + s
	alphabet = list('abcdefghijklmnopqrstuvwxyz')
	# This dictionary stores the occurances.
	occur = {} 
	s_lower = s.lower()
	list_occur = []
	# Going through the alphabet and counting each letter's occurences, and storing this in the dictionary.
	for letter in alphabet:
		occur[letter] = s_lower.count(letter)
	
	result = []
	for key, value in occur.items():
		result.append((value, key))
	result.sort()
	result.reverse()
	return result


