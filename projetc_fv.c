#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
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
// function to remove extension
void remove_extension(char* outputFilename,const char* extension){
    char * position=strstr(outputFilename,extension);
    if (position!=NULL){
        size_t len=strlen(extension);
        memmove(position,position+len,strlen(position+len)+1);
    }
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
char *decompress(const char *chars) {
    char *result = NULL;  
    size_t capacity = 0;  
    size_t size = 0;      
    const char *ptr = chars;

    while (*ptr != '\0') 
    {
        if (*ptr == '\n') {
            if (size + 1 >= capacity) {
                capacity = (capacity == 0) ? 16 : capacity * 2;
                result = realloc(result, capacity);
                if (result == NULL) {
                    perror("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }
            }
            result[size++] = '\n';
            ptr++;
        } else if (isalpha(*ptr)) {
            char current_char = *ptr;
            int num = 0;
            ptr++;
            while (isdigit(*ptr)) {
                num = num * 10 + (*ptr - '0');
                ptr++;
            }
            int repeat = (num > 0) ? num : 1;
            for (int i = 0; i < repeat; i++) {
                if (size + 1 >= capacity) {
                    capacity = (capacity == 0) ? 16 : capacity * 2;  
                    result = realloc(result, capacity);
                    if (result == NULL) {
                        perror("Memory allocation failed");
                        exit(EXIT_FAILURE);
                    }
                }
                result[size++] = current_char;
            }
        } else {
            ptr++;  
        }
    }
    if (size + 1 >= capacity) {
        result = realloc(result, size + 1);
        if (result == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }
    result[size] = '\0';
    return result;
}




int main() {
    int choice;
    printf("Choose mode:\n");
    printf("1. Compression\n");
    printf("2. Decompression\n");
    printf("Enter your choice: ");
    do{
        scanf("%d", &choice);
    }
    while(choice !=1 && choice!=2);
    
    char filename[256];
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
    
    if(choice==1){
    char* compressed = compress(fileContent);
    free(fileContent); 

    if (compressed == NULL) {
        fprintf(stderr, "Compression failed.\n");
        return 1;
    }
    const char* extension = ".txt";
    remove_extension(filename,extension);
    char outputFilename[512]; 
    snprintf(outputFilename, sizeof(outputFilename), "%s_compressed.txt", filename);
    write_file(compressed,outputFilename);
    printf("Compressed content written to %s\n",outputFilename);

    free(compressed); 
    return 0;}
    else if(choice==2){
    char * decompressed=decompress(fileContent);
    if (decompressed == NULL) {
        fprintf(stderr, "Compression failed.\n");
        return 1;
    }
    const char* extension = ".txt";
    remove_extension(filename,extension);
    char outputFilename[512]; 
    snprintf(outputFilename, sizeof(outputFilename), "%s_decompressed.txt", filename);
    write_file(decompressed,outputFilename);
    printf("Decompressed content written to %s\n",outputFilename);
    free(decompressed);


    }
    else{ fprintf(stderr, "Invalid choice.\n");
     return 1;}}