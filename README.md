# MSAIndex
A simple MSA indexing tools to deal with MSA files of an arbitrary size with none standard header entries

Quick start after compilation:

```
  To make an index:
    MSAIndex Index -f example.fasta > example.index 
    
  To Extract fastas:
    If using a file to extract fastas:
      MSAIndex Extract -f example.fasta -i example.index -p file.csv -o outfile.fasta
 
    To extract fastas based on header criteria:
      MSAIndex Extract -f example.fasta -i example.index -s Canada -o outfile.fasta
      This will extract all fastas with Canada in their header
```

Enter nothing to display the help message.

```
Version 0.1.0
Index
  -f Input path to fasta file, Index writes to stdout so make sure to capture output.
Extract
	-f Input path to fasta file, Index writes to stdout so make sure to capture output.
	-i Input path to Index file.
	-p Input path to a file containing a single column of information to sample from.
	-o Name of the file to write extracted fastas too.
	-s String to search for in headers for extraction instead of a list (e.g. Canada).
	
	-h Display this message and exit.
```
