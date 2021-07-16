/*
The main file of the MSA indexing tool, this module is created
mainly to intake the command line options.
*/

#include <iostream>
#include <string>
#include <cstring>
#include "index.h"
#include "extract.h"
#include "tabulate_nucleotides.h"


typedef unsigned long long int __uint64;

void print_help() {
	std::cout << "Version 0.2.0" << std::endl;
	std::cout << "Program execution branches are either Index or Extract." << std::endl;
	std::cout << "E.g. MSA index creation MSAIndex Index -f fasta." << std::endl;
	std::cout << "Index" << std::endl;
	std::cout << "-f Input path to fasta file, Index writes to stdout so make sure to capture output." << std::endl;
	std::cout << "Extract" << std::endl;
	std::cout << "-f Input path to fasta file, Index writes to stdout so make sure to capture output." << std::endl;
	std::cout << "-i Input path to Index file." << std::endl;
	std::cout << "-p Input path to a file containing a single column of information to sample from." << std::endl;
	std::cout << "-o Name of the file to write extracted fastas too." << std::endl;
	std::cout << "-s String to search for in headers for extraction instead of a list (e.g. Canada)." << std::endl;
	std::cout << "Tabulate" << std::endl;
	std::cout << "Currently Reads to stdout" << std::endl;
	std::cout << "-f Input path to fasta file, Index writes to stdout so make sure to capture output." << std::endl;
	std::cout << "-i Input path to Index file." << std::endl;
	std::cout << "-r Specify the header of single reference fasta to use as a mask." << std::endl;
	std::cout << "" << std::endl;
	std::cout << "-h Display this message and exit." << std::endl;

}

int main(int argc, char *argv[]) {
	std::string fasta_file, index_file, sampling_file, output_name, search_string, reference_fasta;
	search_string = "x"; // Default args for sampling extraction
	sampling_file = "x";
	output_name = "Sampled_fastas.fasta";
	fasta_file = "NULL";
	index_file = "NULL";
	reference_fasta = "NULL";
	if (argc == 1) {
		print_help();
		return 0; 
	}
	std::string opt1 = argv[1];
	int branch_execution = 0;
	if (opt1 == "Index") {
		//std::cerr << "Index creation branch" << std::endl;
		branch_execution = 1;
	}
	else if (opt1 == "Extract") {
		//std::cout << "Extraction branch" << std::endl;
		branch_execution = 2;
	}
	else if (opt1 == "Tabulate") {
		branch_execution = 3;
	}
	else
	{
		std::cout << "No option selected: Help" << std::endl;
	}

	for (int i = 0; i < argc; i++) {
		// collect arguments for each execution route
		if (std::strcmp(argv[i], "-f") == 0) {
			fasta_file = argv[i + 1];
		}
		if (std::strcmp(argv[i], "-i") == 0) {
			index_file = argv[i + 1];
		}
		if (std::strcmp(argv[i], "-p") == 0) {
			sampling_file = argv[i + 1];
		}
		if (std::strcmp(argv[i], "-o") == 0) {
			output_name = argv[i + 1];
		}
		if (std::strcmp(argv[i], "-s") == 0) {
			search_string = argv[i + 1];
		}
		if (std::strcmp(argv[i], "-r") == 0) {
			reference_fasta = argv[i + 1];
		}
		if (std::strcmp(argv[i], "-h") == 0) {
			print_help();
			return 0;
		}
	}

	if (fasta_file == "NULL") {
		std::cout << "No fasta file specified." << std::endl;
		return 0;
	}


	if (branch_execution == 1) {
		int index_gen = create_index(fasta_file);
		if (index_gen != 0) {
			std::cerr << "Index Generation failed." << std::endl;
		}
	}
	else if (branch_execution == 2) {
		if ((sampling_file == "x" && search_string == "x") || index_file == "NULL") {
			std::cout << "Missing required argument" << std::endl;
			return 0;
		}
		//std::cout << "Debug beginnign extraction" << std::endl;
		int sampling = extract_fastas(fasta_file, index_file, sampling_file, output_name, search_string);
		if (sampling != 0) {
			std::cout << "Something went wrong extracting fastas." << std::endl;
		}
	
	}
	else if (branch_execution == 3) {
		std::ifstream fasta_f, index_i;
		std::ifstream reference_fa;
		index_i.open(index_file);
		fasta_f.open(fasta_file);
		nucleotides nucs_;
		std::vector<nucleotides> nucs = tabulate_fasta(index_i);
		// pull out reference fasta
		int get_ref = extract_fastas(fasta_file, index_file, "x", "reference_.fasta", reference_fasta);
		std::cerr << reference_fasta << std::endl;
		if (get_ref != 0) {
			std::cerr << "Could not generate reference fasta of " << reference_fasta << std::endl;
			return 0;
		}
		index_i.close();
		reference_fa.open("reference_.fasta");
		get_fasta_single_line(fasta_f, nucs, reference_fa);
		reference_fa.close();
		fasta_f.close();
		
	}
	else {
		print_help();
	
	}

	return 0;

}
