#Homework #3
#concordance.py
#CPTS481
#Alex Hortin
#10732085
from string import whitespace
def concordance(f, unique=True):
	input_file = file(f, 'r')
	concordance_listing,text,word = {},input_file.readlines(), ""#reading in all lines of the input file
	for i in range(len(text)):
		for chars in text[i].lower():
			if chars.isalpha() or chars == "-" or chars == "'": word = word + chars #finding the words 
			else:
				if concordance_listing.has_key(word):	concordance_listing[word][f].append(i)
				elif word != "":	concordance_listing[word] = {f:[i]}
				word = "" 
	for key in concordance_listing: 
		if unique: concordance_listing[key][f] = list(set(concordance_listing[key][f])) #if the unique flag is true erase duplicate line entries
	return concordance_listing
if __name__ == '__main__':
	concordance("therewillbeblood.txt")
	#concordance("therewillbeblood.txt",False)