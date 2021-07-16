#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>


void find_fasta(std::ifstream& index_file, std::string for_extract, std::ifstream& fasta_, std::ofstream& out_file);
int extract_fastas(std::string argv1, std::string argv2, std::string argv3, std::string argv4, std::string argv5);