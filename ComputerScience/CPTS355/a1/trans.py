#	Assignment 1 - Fun with Python
#	Trans.py - Performs a translation based on a ttable requiring 2 tuples and a string
#	9/5/2007	
#	Alex Hortin

def trans(ttable, s):
	if len(ttable[0]) != len(ttable[1]):
		raise ValueError, "The strings in the translation table must have the same length"
	
	#print "Translating " + s + "\n\n"
	print s + "\n\n"	
	tempdict = {}  
	#Create a dictionary for the key value pairs	
	for i in range(len(ttable[0])):
		tempdict[ttable[0][i]] = ttable[1][i]	
	#print tempdict
	s2 = ''
	for i in range(len(s)):
		if (tempdict.has_key(s[i]) == True):
			s2 += tempdict[s[i]]
		else: 
			s2 += s[i]	
	#print s2	
	return s2

def untrans(ttable,s):
	if len(ttable[0]) != len(ttable[1]):
		raise ValueError, "The strings in the translation table must have the same length"
	
	print "Untranslating " + s + "\n\n"
	tempdict = {}  
	#Create a dictionary for the key value pairs	
	for i in range(len(ttable[0])):
		tempdict[ttable[1][i]] = ttable[0][i]	
	#print tempdict
	s2 = ''
	for i in range(len(s)):
		if (tempdict.has_key(s[i]) == True):
			s2 += tempdict[s[i]]
		else: 
			s2 += s[i]	
	#print s2	
	return s2

