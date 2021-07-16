#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

// for now void, will return pointer to a vector in the future
typedef unsigned long long int __uint64;

struct nucleotides {
    __uint64 A = 0;
    __uint64 T = 0;
    __uint64 C = 0;
    __uint64 G = 0;
    __uint64 N = 0;
    __uint64 other = 0;
    __uint64 del = 0;
};

std::vector<nucleotides> tabulate_fasta(std::ifstream& index_file);
void get_fasta_single_line(std::ifstream& input, std::vector<nucleotides> nucs_, std::ifstream& ref_fasta);