#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void decompress(char* chars, char* result) {
    char *newstring = result;
    const char *ptr = chars;

    while (*ptr != '\0') {
        char current_char = *ptr;
        ptr++;
        int num = 1;
        if (isdigit(*ptr)) {
            num = 0;  
            while (isdigit(*ptr)) {
                num = num * 10 + (*ptr - '0');  
                ptr++; 
            }
        }
        for (int i = 0; i < num; i++) {
            *newstring = current_char;
            newstring++;
        }
    }

    *newstring = '\0';  
}

int length(char* chars) {
    int len = 0;
    const char* ptr = chars;

    while (*ptr != '\0') {
        int num = 1;  
        if (isdigit(*(ptr + 1))) {
            num = 0;
            while (isdigit(*(ptr + 1))) {
                num = num * 10 + (*(ptr + 1) - '0');
                ptr++;
            }
        }
        len += num;  
        ptr++; 
    }

    return len;
}
void write_file(const char *input_string, const char *filename) {
    FILE *file = fopen(filename, "w");
    fputs(input_string, file);
    fclose(file);
}

int main() {
    char str[] = "a1b1\nu9r5y7c4\ng5h6\nghj12li\ng5tzui8"; 
    int c = length(str);  
    char result[c + 1]; 
    decompress(str, result); 
    const char *filename = "output.txt";
    write_file(result, filename);
    
}
