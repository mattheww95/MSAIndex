/*
Adding in nucleotide tabulation, using the same method as used by solar fisher.
*/

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "tabulate_nucleotides.h"


typedef unsigned long long int __uint64;



void switch_chars(std::string fasta, std::vector<nucleotides> &tracer) {
    // may inline this decide what to do to it later
    // Leaving as switch statements, as probably faster than applying upper first, need to check this though
    for (__uint64 i = 0; i < fasta.length(); i++) {
        switch (fasta[i])
        {
        case 'A':
            tracer[i].A += 1;
            break;
        case 'T':
            tracer[i].T += 1;
            break;
        case 'C':
            tracer[i].C += 1;
            break;
        case 'G':
            tracer[i].G += 1;
            break;
        case 'N':
            tracer[i].G += 1;
            break;
        case '-':
            tracer[i].del += 1;
            break;
        case 'a':
            tracer[i].A += 1;
            break;
        case 't':
            tracer[i].T += 1;
            break;
        case 'c':
            tracer[i].C += 1;
            break;
        case 'g':
            tracer[i].G += 1;
            break;
        case 'n':
            tracer[i].N += 1;
            break;
        default:
            tracer[i].other += 1;
            break;
        }
    }

}




std::vector<nucleotides> tabulate_fasta(std::ifstream& index_file) {
    /// <summary>
    /// Get the first line of the index file and prepare the buffer for it
    /// </summary>
    /// <param name="fasta_file"></param>
    /// <returns></returns>
    
    // get nth line of the fasta file to prepare a buffer of the appropriate size
    std::string index_value, header, length_value, place_val, total_len;
    // check for uniform size of values
    __uint64 prev_fasta = 0;
    for (size_t i = 0; i != 10; i++) {
        std::getline(index_file, index_value);
        if (i > 1) {
            size_t first_val = index_value.find('\t');
            size_t second_val = index_value.find('\t', first_val + 1);
            __uint64 total_size = std::stoull(index_value.substr(second_val + 1));
            __uint64 tol_size = total_size - first_val;
            if (prev_fasta == 0) {
                prev_fasta = tol_size;
            }
            else {
                if (tol_size != prev_fasta) {
                    std::cerr << "Fastas are not all a uniform length" << std::endl;
                }
            }
        }
       }
    // for arr size use prev_fasta
    // initialize vector of structs
    std::vector<nucleotides> nucs; // create a vector of structs the size of the fastas in the MSA
    for (__uint64 i = 0; i < prev_fasta; i++) {
        nucleotides nucs_;
        nucs.push_back(nucs_); // call default constructor by adding parenthesis to the end of the struct
    }
    std::cerr << "Vector length " << nucs.size() << std::endl;
    return nucs;

}
 
// vector is created, then will be passed off for tallies

// function will return single line fasta only no header
void get_fasta_single_line(std::ifstream& input, std::vector<nucleotides> nucs_, std::ifstream& ref_fasta) {
    // From Rosetta code fasta and cpp reading: http://www.rosettacode.org/wiki/FASTA_format#C.2B.2B
    std::string line, name, content, to_return, ref_fast, ref;
    while (std::getline(input, line).good()) {
        if (line.empty() || line[0] == '>') { // Identifier marker
            if (!name.empty()) { // Print out what we read from the last entry
                //std::cout << name << " : " << content << std::endl;
                switch_chars(content, nucs_);
                name.clear();
            }
            if (!line.empty()) {
                name = line.substr(1);
            }
            content.clear();
        }
        else if (!name.empty()) {
            if (line.find(' ') != std::string::npos) { // Invalid sequence--no spaces allowed
                name.clear();
                content.clear();
            }
            else {
                content += line;
            }
        }
    }
    if (!name.empty()) { // Print out what we read from the last entry
        //std::cout << name << " : " << content << std::endl;
        switch_chars(content, nucs_);
    }

    while (std::getline(ref_fasta, ref_fast).good()) {
        if (ref_fast[0] != '>') {
            ref += ref_fast;
        }
    }

    // final debug read vector chars
    // works, needs a provided reference sample to use for masking
    __uint64 increment = 0;
    __uint64 del_counter = 0; // this dosnt need to be uint64, but just incase one day....
    char ref_nuc;
    std::cout << "Reference_num,Reference_nuc,Position,A,T,C,G,Other,N,Deletion\n";
    for (nucleotides cur_base: nucs_) {
        ref_nuc = ref[increment];
        std::cout << del_counter << "," << ref_nuc << "," << increment;
        std::cout << "," << cur_base.A << "," << cur_base.T << "," << cur_base.C << "," << cur_base.G << "," << cur_base.other;
        std::cout << "," << cur_base.N << "," << cur_base.del << "\n";
        increment++;
        if (ref_nuc != '-') {
            del_counter++;
        }
    }
}






