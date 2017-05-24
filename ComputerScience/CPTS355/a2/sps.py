#	Assignment 2 - An Intrepreter for a PostScript-like Language
#	sps.py - Performs an interpretation of a postscript input
#	9/24/2007	
#	Alex Hortin

import sys, re
import interpret
print "**************************************"
print "*** Python GhostScript Interpreter ***"
print "**************************************"
#print "\n...evaluating input:\n"
parsed_input = [] # This list stores input after it has been parsed.
linear_input = [] # This list stores the parsed input after it has been put into a linear list
stack = [] #This is where the stack will be stored
dictionaryStack = [] #This is where the stack of dictionary entries will be stored
PermDictStackEntry = {}

#asdfd = [2, 3, 4]
#asdf = {}
#asdf["ad"] = asdfd
#print asdf["ad"]

dictionaryStack.append(PermDictStackEntry)
filename = sys.argv[1]
input_file = file(filename, 'r')

text = input_file.readlines() #reading in all lines of the input file
#print text

for line in text:#this is parsing all the lines into a list of lists based on each line for easy access
	parsed_input.append(re.findall('/?[a-zA-Z][a-zA-Z0-9_]*|[-]?[0-9]+|[}{]+|%.*|[^ \t\n]', line))
		

for a in parsed_input:#this is parsing all of the 2d list into one single linear list
	for i in range(len(a)):
		linear_input.append(a[i])
print linear_input

print "...interpreting input"
stack = interpret.interpreter(linear_input,stack,dictionaryStack)

print "...input interpreting complete printing stack (if any errors happened stack will print up to that point):"
print "_Top_"
for a in reversed(stack):
	print a
print "_Bottom_"

