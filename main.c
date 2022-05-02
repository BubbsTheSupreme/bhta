#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int validbin(char *binary) {
	int len = strlen(binary); //get length of string for the loop
	int i;

	for (i = 0; i < len; i++) {
		if (binary[i] == '1' || binary[i] == '0') continue; // if its a 1 or 0 were good
		else return 1; //if not its invalid, return 1 for error
	}

	return 0; // return 0 for valid string
}

int bintoascii(char *binary){
	int i;
	int value = 0; // value of byte
	for (i = 7; i >= 0; i--) {
		if (binary[i] == '1'){ //check if its a 1
			switch(i) { //check the place the 1 is in
				case 7:
					value++; // 1 
					break;
				case 6:
					value += 2; // 2
					break;
				case 5:
					value += 4; // 3
					break;
				case 4:
					value += 8; // 4
					break;
				case 3:
					value += 16; // 5
					break;
				case 2:
					value += 32; // 6
					break;
				case 1:
					value += 64; // 7
					break;
				case 0:
					value += 128; // 8
					break;
			}
		}
	}
	return value;
}

void cvrtbinstr(char *binary, char *delimeter) {
	int i, j;
	char *byte = malloc(8); // array to store byte in
	int len = strlen(binary); // length of binary str 
	int dlen = strlen(delimeter);
	for (i = 0; i < len; i+=8) {
		for (j = 0; j < 8; j++) { //starts from the right of byte
			byte[j] = binary[i+j]; //adds each bit to byte
		}
		if (validbin(byte) == 0) // validates byte
			printf("%c", bintoascii(byte)); //converts the byte
		else 
			printf("[ERROR] Invalid binary input..\n");
		if (binary[i+8] == delimeter[0]) i+=dlen;
	}
	free(byte); //free memory for byte
	printf("\n");
}

void table() {
	int i;
	for (i = 32; i < 127; i++) {
		printf("[%c %d %x] ", i, i, i);
		if ((i % 3) == 0) printf("\n");
	}
	printf("\n");
}

void help() {
	printf("Documentation for Bhta 1.0\n");
	printf("-b [BINARY STRING]     Uses string given as input\n");
	printf("-x -b [BINARY STRING]  Out puts as hex\n");
	printf("-n -b [BINARY STRING]  Out puts as decimal\n");
	printf("-r [FILE NAME]         Reads file given as input.\n");
	printf("-t                     Prints a table of ASCII and hex values (Only characters 32-127)\n");
	printf("-h                     This command..\n");
}

int main(int argc, char *argv[]) {
	int opt;
	char *delimeter;
	char format = 'a'; //ascii default

	while ((opt = getopt(argc, argv, "d:xnb:r:th")) != -1){
		switch(opt) {
			case 'd':
				delimeter = optarg;
				break;
			case 'x':
				format = 'x'; //hex
				break;
			case 'n':
				format = 'n'; //decimal (but since d is for delimeter we use n for number)
				break;
			case 'b':
				cvrtbinstr(optarg, delimeter);
				break;
			case 'r':
				break;
			case 't':
				table();
				break;
			case 'h':
				help();
				break;
		}
	}

	return 0;
}

// GOALS

// [/] OUTPUT TO TERMINAL
// [ ] READ FROM FILE
// [/] VIEW ASCII TABLE
// [/] DELIMETER SUPPORT 

// [/] BIN > ASCII 
// [ ] BIN > DEC
// [ ] BIN > HEX
// [ ] ASCII > BIN
// [ ] ASCII > HEX
// [ ] ASCII > DEC
// [ ] DEC > ASCII
// [ ] DEC > HEX
// [ ] DEC > BIN