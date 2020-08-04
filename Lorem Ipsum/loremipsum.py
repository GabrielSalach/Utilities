import sys
import random

#Syntax : ./loremipsum.py <wrdnbr> (optional)<-o> <output file> 
isOutputing = False

#Syntax of the script
if len(sys.argv) >= 2:
	#First parameter
	if sys.argv[1].isdigit():
		#Assign word number
		wrdNbr = int(sys.argv[1])
	elif sys.argv[1] == "--help":
		#Help page
		print("Help page for the Lorem ipsum generator. Created by Gabriel Salach - 2O2O.\n")
		print("Syntax : python3 loremipsum.py [word count] (options)[-o] [output file path]")
		sys.exit()
	else:
		#Wrong syntax
		print("Invalid parameter. Run loremipsum.py --help to see the correct syntax.")
		sys.exit()

	#Second parameter
	if len(sys.argv) > 2:
		if sys.argv[2] == "-o":
			if len(sys.argv) > 3:
				output = sys.argv[3]
				isOutputing = True
			else:
				print("Wrong output destination. Run loremipsum.py --help to see the correct syntax.")
				sys.exit()
		else:
			print(sys.argv[2]+" is not a valid option. Run loremipsum.py --help to see the correct syntax.")
			sys.exit()
else:
	print("Invalid ammount of parameters. Run loremipsum.py --help to see the correct syntax.")
	sys.exit()


#Declarations
string = "Lorem ipsum dolor sit amet"
point = True
consonnant = "bcdfghlmpqrstv"
vowels = "aeiou"

#Generate a random word. If the parameter is True, the first letter will be uppercase.
#Also, there is a counter for consonnants and vowels so the word can't have more than 2 consecutive letter of each type.
def generateWord(hasPoint):
	length = random.randint(3,8)
	word = list(" ")
	vowelcnt = 0
	conscnt = 0
	for i in range(1,length):
		if bool(random.choice([0,1])):
			conscnt = 0
			if vowelcnt < 2:
				word.insert(i, str(random.choice(vowels)))
				vowelcnt += 1
		else:
			vowelcnt = 0
			if conscnt < 2:
				word.insert(i, str(random.choice(consonnant)))
				conscnt += 1

	if hasPoint == True:
		word[1] = word[1].upper()

	if random.random() < 0.2:
		word += ","
	elif random.random() < 0.1:
		word += "."

	return "".join(word)



#Generate a String.
if wrdNbr < 5:
	string += "."
else:
	string += ","
	for i in range(5,wrdNbr):
		if string.endswith("."):
			string += generateWord(True)
		else:
			string += generateWord(False)
string += "."

if not isOutputing:
	print(string)
else:
	text_file = open(output, "w")
	n = text_file.write(string)
	text_file.close()