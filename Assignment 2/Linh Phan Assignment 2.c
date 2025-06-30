/*============================================================================
| Assignment: pa02 - Calculate the checksum of an input file given:
| -> the name of the input file,
| -> the checksum size of either 8, 16, or 32 bits
| Author: Linh Phan
| Language: c
| To Compile: gcc -o pa02 pa02.c
| To Execute: c -> ./pa02 inputFilename.txt checksumSize
| where inputFilename.txt is the input file
| and checksumSize is either 8, 16, or 32
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
| Class: CIS3360 - Security in Computing - Spring 2025
| Instructor: McAlpin
| Due Date: 3/23/25
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void printOutput(char *text, FILE *output);

void printOutput(char *text, FILE *output) {
	for(int i = 0; i < strlen(text); i++) {
		if (i % 80 == 0 && i != 0) {
			printf("\n");
		}
		fprintf(output, "%c", text[i]);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
// printf("Usage: %s Inputfile checksumSize Outputfile\n", argv[0]);
		return 1;
	}
	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("Error opening file: %s\n", argv[1]);
		return 1;
	}

	int checksumSize = atoi(argv[2]);
	if (!(checksumSize == 8 || checksumSize == 16 || checksumSize == 32)) {
		fprintf(stderr,"Valid checksum sizes are 8, 16, or 32\n");
		return -1;
	}

	char input[1024];
	char j;
	int i = 0;

	while (fscanf(file, "%c", &j) != EOF && i < 1024) {
		input[i] = j;
		i++;
	}

	input[i] = '\0';

	if (checksumSize == 8) {
		unsigned long result = 0;
		for (int k = 0; k < strlen(input); k++) {
			result = result + input [k];
		}
		printOutput(input, stderr);
		printf("\n");
		printf("%2d bit checksum is %8lx for all %4d chars \n", checksumSize, result & 0xff, (int)strlen(input));
	} else if (checksumSize == 16) {
		if (strlen(input) % 2) {
			int lenght = strlen(input);
			input[lenght] = 'X';
			input[lenght + 1] = '\0';
		}
		printOutput(input,stdout);
		unsigned long result = 0;
		for (int k = 0; k <strlen(input); k = k + 2) {
			result = result + (input[k] << 8);
			result = result + (input[k + 1]);
		}
		printf("\n");
		printf("%2d bit checksum is %8lx for all %4d chars\n", checksumSize, result & 0xffff, (int)strlen(input));
	} else {
		while (strlen(input) % 4) {
			int lenght = strlen(input);
			input[lenght] = 'X';
			input[lenght + 1] = '\0';
		}
		printOutput(input, stdout);
		unsigned long result = 0;
		for (int k = 0; k <strlen(input); k = k + 4) {
			result = result + (input[k] << 24);
			result = result + (input[k + 1] << 16);
			result = result + (input[k + 2] << 8);
			result = result + (input[k + 3]);
		}
		printf("\n");
		printf("%2d bit checksum is %8lx for all %4d chars\n", checksumSize, result & 0xffffffff, (int)strlen(input));

	}

	fclose(file);
	fclose(stderr);
	return 0;
}


/*=============================================================================
| I Linh Phan (5666631]) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
