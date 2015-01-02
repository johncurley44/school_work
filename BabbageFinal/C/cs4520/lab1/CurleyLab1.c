/***************************************************************************
 * Name:		   John Curley    
 * Userid:         jmcgdd
 * Course:         CS 4520
 * Assignment#:    Assignment 1
 *
 * File name:      CurleyLab1.c
 *
 * Question no:	   2.26        
 *
 * Assumptions:    1)Input file name is lb1.input
 *		&		   2)Output file name should be lb1.output
 * Precautions	   3)Ensure that you have read and write permissions in the 
 *				   directory 
 * 				   4)
 *				   5)
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <errno.h>

int main(void)
{
	char inputPath[300];
	char outputPath[300];
	char buf[256];
	
	//Ask user for input and output paths
	printf("Please enter path of input file:\n");
	scanf("%s", inputPath);
	printf("Please enter path of output file to write to:\n");
	scanf("%s", outputPath);
	
	// Open input and output files with readonly permissions for the input file
	//	and writing permission for the output file
	int openInput = open(inputPath, O_RDONLY, S_IREAD);
	//Prints error if opening the input file fails.
	if(openInput == -1){
		printf("\n open() on input file failed with error [%s]\n",strerror(errno));
	}
	
	// Output file will be created if it doesn't exist or the file contents will
	//	be deleted if it does exist and written over
	int openOutput = open(outputPath, O_TRUNC | O_CREAT | O_RDWR, S_IRWXU | S_IROTH);
	//Prints error if opening the output file fails.
	if(openOutput == -1){
		printf("\n open() on output file failed with error [%s]\n",strerror(errno));
	}
	
	int writeCheck;
	int numRead;
	//Reads from input file into buffer (buf) 256 characters at a time until
	//	end of file is reached or error is encountered
	while((numRead = read(openInput, buf, sizeof(buf))) > 0){
		//Writes to the output file the number of bytes that were read, based
		//	on numRead, the return value of the read system call
		writeCheck = write(openOutput, buf, numRead);
	}
	//Print error type if error is encountered while trying to read input file
	if(numRead < 0){
		printf("\n read() failed with error [%s]\n",strerror(errno));
	}
	
	//Close both input and output files
	int closeInput = close(openInput);
	int closeOutput = close(openOutput);
	
	return 0;
}