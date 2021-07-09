#include <iostream>
#include <fstream>
#include <string>
#include "index.h"


/*
This module creates the dictionary of fasta with their byte positions

TODO ints for char tracking should be int64
*/

int create_index(std::string argv1);

typedef unsigned long long int __uint64;

int create_index(std::string argv1) {
	// Start by reading bytes between entries
	std::string file_path = argv1;
	std::ifstream fasta1;
	
	fasta1.open(file_path);
	char byte;
	__uint64 watch = 0;
	__uint64 cummulator = 0;
	__uint64 header = 0;
	while (fasta1.get(byte)) {
		if (byte == '>') {
			// ouput cumulative values before switching headers
			std::cout << cummulator - watch << "\t" << watch << std::endl;
			watch = 0;
			header = 1;
			std::cout << byte;
			//std::cout << byte << " " << cummulator << " " << watch << std::endl;
		}else if(header == 1 && byte != '\n') {
			// output the header then nextline
			std::cout << byte;
			watch += 1;
		}
		else if(header == 1 && byte == '\n') {
			// output fasta info until next header
			std::cout << "\t";
			header = 0;
			watch += 1;
		}
		else {
			watch += 1;
		}
		cummulator += 1;
		
	}
	// Deal with last entry
	std::cout << cummulator - watch << "\t" << watch << std::endl;
	return 0;

}