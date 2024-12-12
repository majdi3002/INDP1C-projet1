**Project Overview**
This project provides a tool to compress and decompress text files using a custom encoding method. The tool reduces redundancy in text files by replacing repeated characters with the character and a count, significantly reducing file size for repetitive content.


**Solution Explanation**

The program prompts the user to select a mode:
1 for compression.
2 for decompression.


*readfile function*

The readfile function reads the entire content of a file specified by its name and returns it as a dynamically allocated null-terminated string. It opens the file in read mode, reads it character by character using fgtec, dynamically resizes the memory with realloc to store the content, and ensures proper error handling for file access or memory allocation failures. Finally, it appends a null character ('\0') to mark the end of the string and closes the file.

*Compression*

The compression function replaces sequences of repeated characters with the character followed by its count. For example, "aaabb" becomes "a3b2".In fact , It iterates through the input string, counts consecutive occurrences of each character, and appends the character and its count to a dynamically allocated result string. If a character appears only once, it is added without a count. The result is null-terminated ('\0') and returned.


- Time Complexity: O(n), where "n" is the size of the input string. Each character is processed once.
- Space Complexity: O(n), as we allocate memory proportional to the input size for the output string.

*Decompression*

The decompress function reconstructs the original string from its compressed form. It reads each character and its optional count (if numeric digits follow the character). For each character, it repeats it the specified number of times and writes the result  to the result buffer. The process stops when the end of the compressed string ('\0') is reached. The resulting string is null-terminated ('\0).


- Time Complexity: O(n), where "n" is the size of the compressed string.
- Space Complexity: O(n), as memory for the decompressed string is allocated.

  *length function*
  
The length function calculates the total length of the decompressed string without actually decompressing it. It iterates through the compressed string, parsing each character and its count, summing up the total number of characters based on the counts. This allows the allocation of a correctly sized buffer for decompression.

*Optimality*

This solution is optimal for repetitive text as it achieves significant space savings without sacrificing processing speed.




