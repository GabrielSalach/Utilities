import sys

# List of supported languages.
supportedLanguages = ["Python"]

currentLanguage = None
currentInputFile = None
currentOutputFile = "./README.md"

# Script parameters handling
if len(sys.argv) >= 2:
	# Help page
	if sys.argv[1] == "--help":
		print("DocMe - Readme generator based on code documentation - created by Gabriel Salach")
		print("Version 1.0")
		print("Supported languages : " + str(supportedLanguages))
		print("\nSyntax : docme.py [language] [inputfile] (options)[-o] [output file]")
		sys.exit()

	if len(sys.argv) >= 3:
		# Language handling : if the user input does not correspond to a language specified in the supportedLanguage list, the script exits with an error message.
		for language in supportedLanguages:
			if sys.argv[1] == language:
				currentLanguage = sys.argv[1]
		if currentLanguage == None:
			print("Invalid language name. Run docme.py --help to see the correct syntax.")
			sys.exit()

		# Input file handling : sets the path for the input file.
		currentInputFile = sys.argv[2]

		# Options handling : detects if the user added -o to the command, and if so, sets the output file to the one chosen by the user.
		if len(sys.argv) >= 4:
			if sys.argv[3] == "-o":
				if len(sys.argv) == 5:
					currentOutputFile = sys.argv[4]
				else:
					print("Invalid ammount of parameters. Run docme.py --help to see the correct syntax.")
					sys.exit()
			else: 
				print("Invalid option. Run docme.py --help to see the correct syntax.")
				sys.exit()

	else:
		print("Invalid ammount of parameters. Run docme.py --help to see the correct syntax.")
		sys.exit()
else:
	print("Invalid ammount of parameters. Run docme.py --help to see the correct syntax.")
	sys.exit()

#------------------------------------------------------------------------------------------------------------------------------------------------------------

print("Generating the documentation file for '" + currentInputFile + "' (" + currentLanguage + "). Outputing in : " + currentOutputFile + "...\n")

#Python Handling

if currentLanguage == "Python":
	generatedString = ""
	with open(currentInputFile) as fileobject:
		for line in fileobject:
			flagComment = False
			for char in line:
				if char == '#':
					if flagComment == True:
						generatedString += line
					else:
						flagComment = True

	print(generatedString)
else:
	print("Error : Invalid language.")
	sys.exit()


print("\nDone !")
sys.exit()