**Project Overview**
This project provides a tool to compress and decompress text files using a custom encoding method. The tool reduces redundancy in text files by replacing repeated characters with the character and a count, significantly reducing file size for repetitive content.


**Solution Explanation**

The program prompts the user to select a mode:
1 for compression.
2 for decompression.


*readfile function*

The readfile function reads the entire content of a file specified by its name and returns it as a dynamically allocated null-terminated string. It opens the file in read mode, reads it character by character using fgtec, dynamically resizes the memory with realloc to store the content, and ensures proper error handling for file access or memory allocation failures. Finally, it appends a null character ('\0') to mark the end of the string and closes the file.

*Extension Removal function * 

 It removes the .txt extension from the given filename for processing output filenames.
 

*Compression function*

The compression function replaces sequences of repeated characters with the character followed by its count. For example, "aaabb" becomes "a3b2".In fact , It iterates through the input string, counts consecutive occurrences of each character, and appends the character and its count to a dynamically allocated result string. If a character appears only once, it is added without a count. The result is null-terminated ('\0') and returned.


- Time Complexity: O(n), where "n" is the size of the input string. Each character is processed once.
- Space Complexity: O(n), as we allocate memory proportional to the input size for the output string.

*Decompression function *

The decompress function reconstructs the original string from its compressed form. It reads each character and its optional count (if numeric digits follow the character). For each character, it repeats it the specified number of times and writes the result  to the result buffer. The process stops when the end of the compressed string ('\0') is reached. The resulting string is null-terminated ('\0).


- Time Complexity: O(n+m), where "n" is the size of the compressed string, "m" is the size of the decompressed output string .
- Space Complexity: O(m), as memory for the decompressed string is allocated.

*File Writing function (write_file)*

Writes the given string to a specified file.

*Main Program*

.Provides a CLI(Command-Line Interface) menu for users to:
  -Compress a file.
  -Decompress a file.

.Guides the user through file selection, processing, and naming of output files.

 
*Optimality*

This solution is optimal for repetitive text as it achieves significant space savings without sacrificing processing speed.
In fact :
-Efficiency:
Compression and decompression both process each input character exactly once, ensuring optimal performance.

-Memory Management:
Memory is allocated dynamically and resized as required, avoiding waste and ensuring flexibility.

-Ease of Use:
The CLI provides a simple and intuitive interface for selecting operations and specifying files.

-Error Handling:
Includes error messages for invalid inputs, file access issues, and memory allocation failures, enhancing reliability.


**Instructions for cloning and running the code locally on a machine **

  *Prerequisites:
    -A C compiler (e.g., gcc).
    -A compatible operating system (e.g., Linux, macOS, or Windows).
  *steps to run:
    1)clone the repository:
         git clone <repository-url>
         cd <repository-name>
    2)compile the code :
         gcc -o file_tool main.c
    3)run the code :
         ./file_tool
    4)follow the interactive prompts :
       -For Compression: By selecting option 1 and entering the name of the file to compress,the output will be saved as                          <filename>_compressed.txt.
       -For Decompression: By selecting option 2 and entering the name of the file to decompress,the output will be saved as                      <filename>_decompressed.txt




