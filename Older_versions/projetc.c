#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>

// function for getting file's content
char *readfile(const char *filename){
     FILE *file = fopen(filename, "r");
     if (file == NULL) {   return "file cannot be opened";  }
     
    char *content = NULL;
    size_t totalSize = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF){
        char *newContent = realloc(content, totalSize + 2); 
        if (newContent == NULL) {
            free(content); 
            fclose(file);
            return NULL;
        }


        content = newContent;
        content[totalSize] = ch;
        totalSize++;
        }
    if (content != NULL) {
        content[totalSize] = '\0'; 
                    }   

    fclose(file); 
    return content;  
    
    }


// function to compress the file 's content
char* compress(char* chars) {
    int charsSize = strlen(chars);  
    char* result = malloc((charsSize * 2 + 1) * sizeof(char));  
    int result_index = 0; 
    int count = 1;

    for (int i = 0; i < charsSize; i++) {
        if (i + 1 < charsSize && chars[i] == chars[i + 1]) {
            count++;}
        else {
            result[result_index++] = chars[i];  
            if (count > 1) {
                char countStr[10];
                sprintf(countStr, "%d", count);  
                for (int j = 0; countStr[j] != '\0'; j++) {
                    result[result_index++] = countStr[j];  
                }
            }
            count = 1;  
        }
    }
    result[result_index] = '\0';  

    return result;
}

// function to write result in the file
void write_file(const char *input_string, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    fputs(input_string, file);
    fclose(file);}





// function to decompress file's content
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



int main() {
    int choice;
     printf("Choose mode:\n");
    printf("1. Compression\n");
    printf("2. Decompression\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);


    char filename[256];
    if(choice==1){
    printf("Enter your filename: ");
    if (scanf("%255s", filename) != 1) {
        fprintf(stderr, "Error reading filename.\n");
        return 1;
    }
    char* fileContent = readfile(filename);
    if (fileContent == NULL) {
        fprintf(stderr, "Failed to read file.\n");
        return 1;
    }

    char* compressed = compress(fileContent);
    free(fileContent); 

    if (compressed == NULL) {
        fprintf(stderr, "Compression failed.\n");
        return 1;
    }
    char outputFilename[512]; 
    snprintf(outputFilename, sizeof(outputFilename), "%s_compressed", filename);
    write_file(compressed,outputFilename);
    printf("Compressed content written to %s\n",outputFilename);

    free(compressed); 
    return 0;}
    else if(choice==2){printf("Enter your filename: ");
    if (scanf("%255s", filename) != 1) {
        fprintf(stderr, "Error reading filename.\n");
        return 1;
    }
    char* fileContent = readfile(filename);
    if (fileContent == NULL) {
        fprintf(stderr, "Failed to read file.\n");
        return 1;
         }
    int c = length(fileContent);  
    char result[c + 1]; 
    decompress(fileContent, result);
    if (result == NULL) {
        fprintf(stderr, "Compression failed.\n");
        return 1;
    }
    char outputFilename[512]; 
    snprintf(outputFilename, sizeof(outputFilename), "%s_decompressed", filename);
    write_file(result,outputFilename);
    printf("Compressed content written to %s\n",outputFilename);



    }
    else{ fprintf(stderr, "Invalid choice.\n");
        return 1;}
}
