#include <stdio.h>
#include <stdlib.h>
#include<string.h>

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



int main() {
    const char* filename = "majdi.txt"; 
    char*m = readfile(filename); 
    char* compressed = compress(m); 
    printf("Original content: %s\n", m);
    printf("Compressed string: %s", compressed); 
    return 0;
}

