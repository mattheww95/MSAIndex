#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "extract.h"
#include <bits/stdc++.h>

/*
TODO ints for char tracking should be int64
TODO add in option for command line to extract sample based on header name
*/
typedef unsigned long long int __uint64;

void find_fasta(std::ifstream &index_file, std::string for_extract, std::ifstream &fasta_, std::ofstream &out_file);
int extract_fastas(std::string argv1, std::string argv2, std::string argv3, std::string argv4, std::string argv5);

int extract_fastas(std::string argv1, std::string argv2, std::string argv3, std::string argv4, std::string argv5) {

	std::string fasta_path = argv1;
	std::string dict_path = argv2;
	std::string to_extract = argv3; // change this to some list
	std::string out_file_name = argv4;
	std::string criteria_extract = argv5;
	std::cerr << argv1 << std::endl;
	
	//open files
	std::ifstream fasta_file; 
	fasta_file.open(fasta_path);
	std::ifstream dict_file; 
	dict_file.open(dict_path);
	std::ofstream fastas_out;
	fastas_out.open(out_file_name);
	std::cerr << "All files open!" << std::endl;
	std::string fasta_line;
	if (to_extract != "x") {
		std::ifstream extraction;
		extraction.open(to_extract);
		if (extraction.good()) {
			while (getline(extraction, fasta_line).good()) {
				find_fasta(dict_file, fasta_line, fasta_file, fastas_out);
				dict_file.clear();
				dict_file.seekg(0, dict_file.beg);
			}
		}
		fastas_out.close();
		dict_file.close();
		fastas_out.close();
		extraction.close();
		return 0;
	}
	else if (criteria_extract != "x") {
		find_fasta(dict_file, criteria_extract, fasta_file, fastas_out);
		fastas_out.close();
		dict_file.close();
		fastas_out.close();
		return 0;
	}
	fastas_out.close();
	dict_file.close();
	fastas_out.close();
	return 0; 

}



void find_fasta(std::ifstream &index_file, std::string for_extract, std::ifstream &fasta_, std::ofstream &out_file) {
	std::string line_dict, fasta_header, beginning, end;
	// fields in the dictionary created
	// TODO sometimes binary line endings show up, could be locale related
	std::size_t fasta_sn, start_sn;
	while (getline(index_file, line_dict).good()) {
		fasta_sn = line_dict.find('\t');
		start_sn = line_dict.find("\t", fasta_sn + 1);
		//std::cout << " " << start_sn << " ";
		//to_sn = line_dict.find("\t", start_sn + 1);
		fasta_header = line_dict.substr(0, fasta_sn);
		beginning = line_dict.substr(fasta_sn + 1, start_sn);
		std::string begin_ = beginning.substr(0, beginning.find("\t"));
		end = line_dict.substr(start_sn + 1);
		//std::cout << fasta_header << std::endl;
		size_t test_ex = fasta_header.find(for_extract, 0);
		if (test_ex != std::string::npos) { // search header for criteria slower... but easier
			// write out that fastas
			__uint64 start_index = std::stoull(begin_, nullptr, 10);
			__uint64 end_pos = std::stoull (end, nullptr, 10);
			fasta_.seekg(start_index, std::ios::beg);
			char* buffer = new char[end_pos]; // Create array size of the end postion
			fasta_.read(buffer, end_pos); // read in that many characters
			//out_file << buffer << "\n";
			//TODO: this is meant to be temporary (the carat addition)
			out_file << ">";
			for (__uint64 i = 0; i != end_pos; i++) {
				out_file << buffer[i];
			}
			out_file << "\n";
			delete[] buffer; // clear new buffer

		}
		line_dict.clear();
		continue;
	}
	
}