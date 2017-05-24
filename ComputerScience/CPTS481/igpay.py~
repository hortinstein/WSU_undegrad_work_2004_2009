#Homework #1
#igpay.py
#CPTS481
#Alex Hortin
#10732085


from string import uppercase
from string import capitalize
def igpay(str):
	strcpy = str
	str = str.lower()
	vowel = ["a", "e", "i", "o", "u"]			
	for v in vowel:
		if v in str:
			if str[0:1] in vowel:
				return str + "way"
			c = str[0]		
			while c[-1] not in vowel:
				str = str[1::]		
				c = c + str[0]
			if strcpy[0] in uppercase: str = capitalize(str)	
			return str + c[:-1] + "ay"		
	return str

if __name__ == '__main__':
	# The code that follows will *only* be executed when this is being
	# run directly, not imported.
	print "igpay(\"bad\"): " + igpay("bad")
	print "igpay(\"groovy\"): " + igpay("groovy")
	print "igpay(\"add\"): " + igpay("add")
	print "igpay(\"office\"): " + igpay("office")
	print "igpay(\"yes\"): " + igpay("yes")
	print "igpay(\"why\"): " + igpay("why")
	print "igpay(\"The\"): " + igpay("The")
	
