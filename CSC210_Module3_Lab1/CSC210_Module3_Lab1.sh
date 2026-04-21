#!/bin/bash

# -----------------------------------------------------------------------------------------------------------
# File Name: CSC210_Module3_Lab1.sh
# Author: Alejandro Panotja-Zurita
# Date Created: September 13, 2025
# Class: CSC 210: System Programming
# Assignemnt: Module 3 - Lab 1: Scripts Lab
# Instructor: Tian Z. Ding
# Purpose of Script: Script was created as part of a class assignment design to get familiar with bash. This
# bash script creates a directory and a file before modifying the contents. Upon completion the files are 
# removed. 
# -----------------------------------------------------------------------------------------------------------

# Prompt user to enter their name.
echo "--------------------------------------------------------------"
echo "Enter name of user below to proceed."
echo ""
echo -n "Name: "
read userName
echo ""

# Greet user using stored named.
echo "Hello $userName!"
echo "--------------------------------------------------------------"

# Prompt user to enter the name of directory to be created.
echo -n "Creating new directory in: "
pwd
echo ""

echo -n "Enter the name of directory to be created: "
read newDirectory
echo ""

# Create new directory based on user input.
mkdir "$newDirectory"

# Inform user of newly created directory.
echo "${newDirectory} directory has been successfully created!"
echo "--------------------------------------------------------------"

# Inform user that we are now moving into newly created folder.
echo "changing working directory to:"
echo ""
cd "${newDirectory}"
pwd
echo "--------------------------------------------------------------"

# Prompt user to enter the name of new file to be created.
echo "Creating new text file in:"
echo ""
pwd
echo "--------------------------------------------------------------"

echo -n "Enter the name of text file to be created: "
read newFile
echo ""

# Create new text file based on user input.
touch "${newFile}.txt"

# Inform user of newly created file
echo "${newFile}.txt has been successfully created!"
echo "--------------------------------------------------------------"

 # Add sample text into file that was created.
 echo "${newFile}.txt was created using a script by $userName" > "${newFile}.txt"
 echo "Sample text has been added to $newFile.txt"
 
 echo ""
 echo "SAMPLE TEXT: '$newFile.txt was created using a script by $userName'"
 echo "--------------------------------------------------------------"
 
 # Create a copy of the file that was created.
 cp "${newFile}.txt" "${newFile}_Copy.txt"
 echo "Copy of $newFile.txt file has been successfully created in:"
 echo ""
 pwd
 echo "--------------------------------------------------------------"
 echo "Current files in directory: "
 echo ""
 ls
 echo "--------------------------------------------------------------"
 
 # Remove the files that have been created.
 echo "Removing files created by this script."
 echo ""
 rm "${newFile}.txt"
 echo "${newFile}.txt has been successfully removed."
 echo ""
 rm "${newFile}_Copy.txt"
 echo "${newFile}_Copy.txt has been successfully removed."
 echo "--------------------------------------------------------------"
 echo "Current files in directory: "
 echo ""
 ls
 echo "--------------------------------------------------------------"
 
 # Change working directory
 cd ..
 echo "Working directory successfully changed to:"
 echo ""
 pwd
 echo "--------------------------------------------------------------"
 
 # Remove directory that was created.
 echo "Current files in directory: "
 echo ""
 ls
 echo "--------------------------------------------------------------"
 rmdir "$newDirectory"
 echo "$newDirectory directory has been successfully removed."
 echo ""
 echo "--------------------------------------------------------------"
 echo "Current files in directory: "
 echo ""
 echo "--------------------------------------------------------------"

# Notify user that the script has finished.
echo "CSC210_Module3_Lab1.sh Script was successfully executed!" 
