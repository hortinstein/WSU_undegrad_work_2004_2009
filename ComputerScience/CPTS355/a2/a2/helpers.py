#	Assignment 2 - An Intrepreter for a PostScript-like Language
#	sps.py - Performs an interpretation of a postscript input
#	9/24/2007	
#	Alex Hortin

#isanum
#checks to see if the string is a number
#input 	string
#output bool
#9/24/2007
def isNum(str):
    from string import digits #imports the digits library
    for c in str:
        if not c in digits: return 0
    return 1

#findMatch
#interates the string and looks for a match
#input 	the stack so it can modify
#		the list of commands so it can iterate through looking for a match
#		the current position of the iterator in the command stack
#		the char whose match your looking for
#output the new iterator position
#		it will also modify the stack by pushing the suspended value onto the stack 
#9/24/2007
def findMatch(stack, psCommands, i, char):
	tempParenString = ""			
	parenCount=1	
	i+=1			
	while parenCount > 0:				
		if (psCommands[i] == ")" and char == "(") or (psCommands[i] == "}" and char == "{"):
			parenCount=parenCount-1
		elif psCommands[i] == char:
			parenCount=parenCount+1
		elif char == "{":
			tempParenString += (psCommands[i]) + " " 		
		else :
			tempParenString += (psCommands[i])
		if (parenCount != 0):		
			i+=1

	if char == "(":
		tempParenString = "(" + tempParenString + ")"
		print tempParenString	
	stack.append(tempParenString) 
	#print "in findmath"
	#print stack
		
	return (i) 

#roll
#interates the string and looks for a match
#input 	the stack so it can modify
#output error bool
#		it will also modify the stack to reflect the roll
#9/24/2007
def roll(stack):
	num_roll = stack.pop()#seeing how many rolling iterations are needed
	num_obj = stack.pop()#seeing the number of objects involved
	if int(num_obj) > len(stack):
		print "...number of objects in roll is greater than number on the stack;skipping roll"	
		return	1 
	rollIt = 0
	temp_stack = []#defining a temp stack to do iterations
	#print "number of objects" + str(num_obj)
	#print "number of rolls" + str(num_roll)
	#print "stack" + str(stack)
	while rollIt < int(num_obj):
		#print rollIt
		#print stack
		temp_stack.append(stack.pop())#poping off the values onto the temp stack
		rollIt+=1
	rollIt = 0
	while rollIt < int(num_roll):
		temp_stack.append(temp_stack.pop(0))#looping the top value by popping it than appending it to the front
		rollIt+=1
	temp_stack.reverse()
	for i in range(len(temp_stack)):
		stack.append(temp_stack[i])#reappending the rolled temp stack to the real one
	return 0
#priorDef
#tries to see if the dictionary stack is defined
#input 	the dictionary stack
#output bool
#9/24/2007
def priorDef(name,dictionaryStack):
	for cur_dict in dictionaryStack:
		if cur_dict.has_key(name):#checking to see if the key exists
			return (1 == 1)
		else:
			return (1 == 0)

#defineName
#tries to see if the dictionary stack is defined
#input 	the dictionary stack
#output bool
#9/24/2007
def defineName(name,dictionaryStack):
	for cur_dict in dictionaryStack:
		if cur_dict.has_key(name):#checking for a key
			return cur_dict[name]#returning that key
		else:
			print "No key"

#errorCheck
def errorCheck(stack,psCommands,i):
	#error checking for 3 pop statements
	if (psCommands[i] == "ifelse") and (len(stack) < 3):
		print "...Not enough elements in the stack to perform the: " + str(i) + "th command of " + psCommands[i] + " , terminating"
		return 1
	#error checking for 2 pop statements
	elif ((psCommands[i] == "add") or (psCommands[i] == "mul") or (psCommands[i] == "sub") or (psCommands[i] == "div") or (psCommands[i] == "lt") or (psCommands[i] == "gt") or (psCommands[i] == "eq") or (psCommands[i] == "and") or (psCommands[i] == "def") or (psCommands[i] == "exch") or (psCommands[i] == "if") or psCommands[i] == "or") and (len(stack) < 2):
		print "...Not enough elements in the stack to perform the: " + str(i) + "th command of " + psCommands[i] + " , terminating"
		return 1
	#error checking for 1 pop statements
	elif ((psCommands[i] == "=") or (psCommands[i] == "not") or (psCommands[i] == "dup") or (psCommands[i] == "pop")) and (len(stack) < 1):
		print "...Not enough elements in the stack to perform the: " + str(i) + "th command of " + psCommands[i] + " , terminating"
		return 1
	


