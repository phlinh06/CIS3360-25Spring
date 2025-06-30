/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Linh Phan
| Language: c
| To Compile: gcc -o pa01 pa01.c
| To Execute: or c -> ./pa01 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Spring 2025
| Instructor: McAlpin
| Due Date: 2/23/25
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ROWS 9
#define MAX_COLS 9
#define MAX_SIZE 10000

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s filename\n", argv[0]);
		return 1;
	}

	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("Error opening file: %s\n", argv[1]);
		return 1;
	}

	int matrix[MAX_ROWS][MAX_COLS];
	int rows = 0, cols = 0;
	int size = 0;
	if (fscanf(file, "%d", &size) == 1)
	{
		if (fgetc(file) == '\n')
		{
			rows = 0;
			cols = 0;
		}
	}
	while (fscanf(file, "%d", &matrix[rows][cols]) == 1) {
		cols++;
		if (fgetc(file) == '\n') {
			rows++;
			cols = 0;
		}
	}
	printf("\nKey matrix:\n");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%4d ", matrix[i][j]);
		}
		printf("\n");
	}
	fclose(file);

	file = fopen(argv[2], "r");
	if (file == NULL) {
		printf("Error opening file: %s\n", argv[2]);
		return 1;
	}

	char arrayBefore[MAX_SIZE];
	int index = 0;
	int length = 0;

	while (fscanf(file, "%c", &arrayBefore[index]) == 1 && index < MAX_SIZE - 1) {
		if (isalpha(arrayBefore[index])) {
			arrayBefore[index] = tolower(arrayBefore[index]);
			index++;
		}
	}
	length = index;

	fclose(file);

	int padLength = size - length%size;
	for (int i = 0; i < padLength ; i++) {
		arrayBefore [length+ i] = 'x';
	}

	length = length + padLength;

	length = length + length % size;
	index = 0;

	printf("\nPlaintext: \n");
	while(index < length) {
		for (int j = 0; j < 80 && index < length; j++, index++) {
			putchar(arrayBefore[index]);
		}
		printf("\n");
	}
	int arrayAfter[MAX_SIZE];

	for(int i = 0; i < length; i++) {
		arrayAfter[i] = arrayBefore[i] - 'a';
	}

	printf("\n");

	printf("Ciphertext: \n");
	int encrypted[MAX_SIZE];
	for (int i = 0; i < length; i += size) {
		int block[size];
		for (int j = 0; j < size; j++) {
			block[j] = arrayAfter[i + j];
		}
		for (int j = 0; j < size; j++) {
			encrypted[j+i] = 0;
			for (int k = 0; k < size; k++) {
				encrypted[j+i] = (encrypted[j+i] + matrix[j][k] * block[k]);
			}
		}
	}

	char encrypText[MAX_SIZE];
	for (int i = 0; i < length; i++) {
		encrypText[i] = (encrypted[i]%26) + 'a';
	}

	index = 0;

	while(index < length) {
		for (int i = 0; i < 80 && index < length; i++) {
			printf("%c", encrypText[index]);
			index++;
		}
		printf("\n");
	}

	return 0;
}

/*=============================================================================
| I Linh Phan (5666631) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
