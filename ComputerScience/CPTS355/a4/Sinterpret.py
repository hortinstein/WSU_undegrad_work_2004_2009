#	Assignment 2 - An Intrepreter for a PostScript-like Language
#	sps.py - Performs an interpretation of a postscript input
#	9/24/2007	
#	Alex Hortin

import Shelpers#imports my file of helper functions


isStart = True
#interpreter
#parses through the command stack deciding what action to take 'i' is used as the pointer on the command stack
#input 	list of strings for the Parsed commands
#		the current execution stack (a list of strings
#		Dictionary for the dictionary stack
#output string returning the stack
#9/24/2007
def interpreter(psCommands,stack,dictionaryStack,fp):
	#print stack 
	#The for loop to handle all of that commands
	i=0 #this is essentially the command stack pointer
	global isStart

	while i < len(psCommands):
		#print psCommands[i]
		#print stack
		#print str(i) + " number command meaning: " + str(psCommands[i])
		#error checking for statments that require more elements than are on the stack		
		if (Shelpers.errorCheck(stack,psCommands,i) == 1):
			break
		if (type(psCommands[i]) == type(3) ):
			isStart = True
			stack.append(psCommands[i])#if it is a number it is appended to the stack
		
		elif Shelpers.isNum(psCommands[i]):#checks to see if it is a number
			stack.append(psCommands[i])#if it is a number it is appended to the stack
		
		elif psCommands[i] == "true":#handling the true command
			stack.append(1 == 1)
		elif psCommands[i] == "false":#handling the false command
			stack.append(1 == 0)
	#Handling the Built in Operators		
		
		elif psCommands[i] == "add":#handling the add command
			stack.append((int)(stack.pop()) + (int)(stack.pop()))
		elif psCommands[i] == "mul":#handling the mul command
			stack.append((int)(stack.pop()) * (int)(stack.pop()))
		elif psCommands[i] == "sub":#handling the sub command
			int1 = int(stack.pop())
			int2 = int(stack.pop())
			stack.append((int2 - int1))
		elif psCommands[i] == "div":#handling the div command
			int1 = int(stack.pop())
			int2 = int(stack.pop())
			stack.append((int2 / int1))
		elif psCommands[i] == "lt":#handling the lt command
			stack.append((int)(stack.pop()) > (int)(stack.pop()))
		elif psCommands[i] == "gt":#handling the gt command
			stack.append((int)(stack.pop()) < (int)(stack.pop()))
		elif psCommands[i] == "eq":#handling the eq command
			stack.append(stack.pop() == stack.pop())
		elif psCommands[i] == "and":#handling the and command
			cond1 = stack.pop()	
			cond2 = stack.pop()
			stack.append(cond1 and cond2 )
		elif psCommands[i] == "or":#handling the and command
			cond1 = stack.pop()	
			cond2 = stack.pop()
			stack.append(cond1 or cond2 )
			#print stack
		elif psCommands[i] == '=':#handling the or command
			print stack.pop()	
		elif psCommands[i] == "not":#handling the not command
			stack.append( bool(stack.pop() - 1) )
	#Making sure that any uncontained closing ')' or '}' will be caught			
		elif (psCommands[i] == ")"):#handling the parenthesis
			print "...')' mismatch please check input file" 
			break
		elif (psCommands[i] == "}"):#handling the parenthesis
			#print i			
			print "...'}' mismatch please check input file"
			break
	#Handling the commands that suspend execution with { } or push strings contained with ( )
		elif psCommands[i] == "(":#handling the parenthesis
			i = Shelpers.findMatch(stack, psCommands, i, "(")
		elif psCommands[i] == "{":#handling the parenthesis 
			tempStoreIt = i
			i = Shelpers.findMatch(stack, psCommands, i, "{")
	
			stack.pop() #getting rid of the string type entry on the stack and placing a list on there
						
			stack.append(psCommands[tempStoreIt+1:(i)])
			

	#Hadnling the conditional statements	
		elif psCommands[i] == "if":#handling the if command		
			command = stack.pop()#storing the true command			
			case = stack.pop()			
			if (case == bool(1)):#checking the condition on the stack			
				stack = interpreter(command,stack,dictionaryStack,fp)
	
		
		elif psCommands[i] == "ifelse":#handling the ifelse command
			commandFalse = stack.pop()#storing the true command
			commandTrue = stack.pop()#storing the false command
			if (stack.pop() == bool(1)):#checking the condition on the stack
				interpreter(commandTrue,stack,dictionaryStack,fp)
			else:
				interpreter(commandFalse,stack,dictionaryStack,fp)
	#Handling the name constants
		elif (psCommands[i])[0:1] == "/":#handling the name / command
			stack.append((psCommands[i][1::]))#if it is a name it is appended to the s

	#Handling the stack operations
		elif (psCommands[i] == "dup"):
			d = stack.pop()
			stack.append(d)
			stack.append(d)
		
		elif (psCommands[i] == "exch"):
			d = stack.pop()
			d2 = stack.pop()
			stack.append(d)
			stack.append(d2)
		elif (psCommands[i] == "pop"):
			stack.pop()
		elif (psCommands[i] == "roll"):
			error = Shelpers.roll(stack)
			if error != 0:
				break
	#Handling the Dictionary and Def operations
		#print "right before prior def"
		#print psCommands[i]
		#print stack
		#print "hello"
		elif (psCommands[i] == "def") and len(stack) > 1:
			value = stack.pop()			
			name = stack.pop()

			d = (Shelpers.staticLink,{name: value})
			dictionaryStack.insert(Shelpers.counter,d)#hashes the value in the dictionary	
			Shelpers.counter = Shelpers.counter + 1
			Shelpers.offcounter = Shelpers.staticLink+1
			if (type(value) == type([])):
				Shelpers.staticLink = Shelpers.staticLink+Shelpers.offcounter	
								
		elif (psCommands[i] == "clear"):
			stack = []
		elif (psCommands[i] == "stack"):
			print stack
		else:
			if isStart == True:
				Shelpers.index = Shelpers.counter		
			
			if (Shelpers.priorDef(psCommands[i],dictionaryStack)):
				cmd = (Shelpers.defineName(psCommands[i],dictionaryStack))	
				isStart = False  
				if type(cmd) == type(3) or type(cmd) == type("ohwoot"):
					temp_int = cmd
					cmd = []
					stack.append(temp_int)
					isStart = True
				else:
					Shelpers.last = Shelpers.counter - 1
					interpreter(cmd,stack,dictionaryStack,fp)
					#print Shelpers.last
					dictionaryStack[Shelpers.last:] = []
					Shelpers.staticLink = Shelpers.last-1
					Shelpers.counter = Shelpers.last	
					
					
	
		
		i+=1	
	return stack
