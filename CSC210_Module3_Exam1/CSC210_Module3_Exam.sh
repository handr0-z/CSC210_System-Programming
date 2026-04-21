#!/bin/bash

# -----------------------------------------------------------------------------------------------------------
# File Name: CSC210_Module3_Exam.sh
# Author: Alejandro Panotja-Zurita
# Date Created: September 20, 2025
# Class: CSC 210: System Programming
# Assignemnt: Module 3 - Exam
# Instructor: Tian Z. Ding
# Purpose of Script: Script was created as part of a class exam designed to get familiar with bash. This
# script creates a directory and multiple files before modifying the contents.
# -----------------------------------------------------------------------------------------------------------
# I referenced the following websites to understand how to properly set up an if else statement in bash:
# https://stackoverflow.com/questions/68622119/how-to-use-if-elif-else-in-bash. Aside from that i also 
# referenced https://kapeli.com/cheat_sheets/Bash_Test_Operators.docset/Contents/Resources/Documents/index
# for a list of test operators that could be used inside If statements, Lastly I also looked at chatGPT to 
# obtain understanding of bass commands that may be used to accomplish a task, such as the grep command, which
# was used in an If statement within my code to verify contents of a file.
# -----------------------------------------------------------------------------------------------------------

# Define variables needed to run program.
declare -i int=0 
declare -a newFile # Array declared
declare -a fileContent # Array declared

# Define function used to create new directory
createDirectory()
{
	# Prompt user to enter the name of directory to be created.
	echo -n "Creating new directory in: "
	pwd
	echo ""

	echo -n "Enter the name of directory to be created: "
	read newDirectory
	echo ""
	
	# Check if directory already exist, if yes - delete before proceeding.
	if [ -d "$newDirectory" ] ; then
		# Remove directory that was created.
		echo "$(pwd)/$newDirectory directory already exists..."
		echo ""
		echo "Deleting $(pwd)/$newDirectory directory."
		echo "--------------------------------------------------------------"
		rm -ri "$newDirectory" # removes directory, confirms with user before deleting files located inside.
		echo "$newDirectory directory has been successfully removed."
		echo "--------------------------------------------------------------"
	fi

	# Create new directory based on user input.
	mkdir "$newDirectory"

	# Inform user of newly created directory.
	echo "${newDirectory} directory has been successfully created!"
	echo "--------------------------------------------------------------"
}

# Define function used to create .txt files.
createTextFile()
{
	# Prompt user to enter the name of new file to be created.
	echo "Creating new text file in:"
	echo ""
	pwd
	echo "--------------------------------------------------------------"

	echo -n "Enter the name of text file to be created: "
	read input
	newFile[$int]="$input" # take input from user and store in variable
	echo ""

	# Create new text file based on user input.
	touch "${newFile[$int]}.txt"

	# Inform user of newly created file
	echo "${newFile[$int]}.txt has been successfully created!"
	echo "--------------------------------------------------------------"

	# Promp user to provide the content inside the new file
	echo "Enter text to be included inside ${newFile[$int]}.txt: "
	echo ""
	read input
	fileContent[$int]="$input"  # take input from user and store in variable
	echo "${fileContent[$int]}" > "${newFile[$int]}.txt"
	echo ""

	# Inform user of newly created file
	echo "${newFile[$int]}.txt has been successfully updated!"
	echo "--------------------------------------------------------------"
	
	#increment for integer for next file to be created
	((int++))	
}

# Define function used to combine .txt files created previously
combineTextFiles()
{
	echo "Creating 3rd file using ${newFile[$((int - 1))]}.txt & ${newFile[$((int - 2))]}.txt in:"
	echo ""
	pwd
	echo "--------------------------------------------------------------"
	
	echo -n "Enter the name of 3rd .txt file to be created: "
	read input
	newFile[$int]="$input" # take input from user and store in variable
	echo ""

	# Create new text file based on user input.
	touch "${newFile[$int]}.txt"
	
	# Merge content inside previously created files into new file.
	cat "${newFile[$((int - 2))]}.txt" >> "${newFile[$int]}.txt" # file1
	echo "" >> "${newFile[$int]}.txt" # Spacing between file contents
	cat "${newFile[$((int - 1))]}.txt" >> "${newFile[$int]}.txt" # file2
	
	# Inform user of newly created file
	echo "${newFile[$int]}.txt has been successfully created!"
	echo "--------------------------------------------------------------"
}

# Define a function used to search a .txt file for a term provided by user.
searchFile()
{
	echo "Enter term used to verify the contents of ${newFile[$int]}.txt below:"
	echo ""
	echo -n "SEARCH TERM: "
	read searchTerm
	echo "--------------------------------------------------------------"
	
	# Check if search term provided is located within combined,
	if grep -q "${searchTerm}" "${newFile[$int]}.txt" ; then
		# Inform user that combined file contains search term
		echo "Success!"
		echo ""
		echo "'${searchTerm}' found inside ${newFile[$int]}.txt."
		echo "--------------------------------------------------------------"
	else
		# Informl user that combined file does not contain search term.
		echo "Error."
		echo ""
		echo "'${searchTerm}' not found inside ${newFile[$int]}.txt."
		echo "--------------------------------------------------------------"
	fi
	
	# Display contents of Combined file on terminal to show user contents and provide confirmation search results.
	echo "${newFile[$int]}.txt FILE CONTENTS:"
	echo ""
	cat "${newFile[$int]}.txt"
	echo ""
	echo "SEARCH TERM PROVIDED: ${searchTerm}"
	echo ""
	echo "--------------------------------------------------------------"
	
}

# Prompt user to enter their name.
echo "--------------------------------------------------------------"
echo "Enter name of user below to proceed."
echo ""
echo -n "Name: "
read userName
echo ""
echo "--------------------------------------------------------------"

# Greet user using stored named.
echo "Hello $userName!"
echo "--------------------------------------------------------------"

# Create new directory based on user input.
createDirectory

# Inform user that we are now moving into newly created folder.
echo "changing working directory to:"
echo ""
cd "${newDirectory}"
pwd
echo "--------------------------------------------------------------"

# Create first .txt file per user prompts
createTextFile

# Create second .txt file per user prompts
createTextFile 
 
# Merge (2) files created previously into new file.
combineTextFiles

# Verify contents of combined file with user input.
searchFile

# Notify user that the script has finished.
echo "CSC210_Module3_Exam.sh Script was successfully executed!"
echo ""
echo "--------------------------------------------------------------"

