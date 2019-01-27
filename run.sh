#!/bin/bash

# Usage: ./run.sh <mode> <file>
# 	mode: scan|tokens|parse|pretty|symbol|typecheck|codegen
                                
# Check the command-line arguments are valid

if [ $# -lt 2 ]
then
	echo "Missing arguments"
	echo "Usage: $0 <mode> <file>"
	echo " + mode: scan|tokens|parse|pretty|symbol|typecheck|codegen"
	echo " + file: path to file (absolute or relative)"
	exit 1
fi

if [[ "|scan|tokens|parse|" != *"|$1|"* ]]
then
	echo "Unknown mode \"$1\""
	echo "Usage: $0 <mode> <file>"
	echo " + mode: scan|tokens|parse|pretty|symbol|typecheck|codegen"
	echo " + file: path to file (absolute or relative)"
	exit 1

fi

# Invoke the compiler with the provided arguments: mode ($1) and file ($2)
#
# You MUST replace the following command with the command for invoking your compiler
#!/bin/bash

if [ "$1" = "tokens" ]
then
	./src/tokens/minitokens "$1" < "$2"
elif [ "$1" = "scan" ]
then 
	./src/scanner/miniscanner "$1" < "$2"
elif [ "$1" = "parse" ]
then
	./src/scanner+parser/minic "$1" < "$2"
else
	echo "Incorrect mode argument!"
	exit 1
fi
