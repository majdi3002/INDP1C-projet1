**Project Overview**
This project provides a tool to compress and decompress text files using a custom encoding method. The tool reduces redundancy in text files by replacing repeated characters with the character and a count, significantly reducing file size for repetitive content.


**Solution Explanation**

*Compression*
The compression function replaces sequences of repeated characters with the character followed by its count. For example, "aaabb" becomes "a3b2".

- Time Complexity: O(n), where "n" is the size of the input string. Each character is processed once.
- Space Complexity: O(n), as we allocate memory proportional to the input size for the output string.

*Decompression*
The decompression function reconstructs the original text by expanding encoded sequences.

- Time Complexity: O(n), where "n" is the size of the compressed string.
- Space Complexity: O(n), as memory for the decompressed string is allocated.

*Optimality*
This solution is optimal for repetitive text as it achieves significant space savings without sacrificing processing speed.
