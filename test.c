#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>



// function to compress the string
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
                result = (char*)realloc(result, capacity);
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
                    result =(char*)realloc(result, capacity);
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
        result =(char*) realloc(result, size + 1);
        if (result == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }
    result[size] = '\0';
    return result;
}


// Function to compress the string
char* compress(char* chars) {
    int charsSize = strlen(chars); 
    char* result = (char*)malloc((charsSize * 2 + 1) * sizeof(char));
 
    int result_index = 0; 
    int count = 1;

    for (int i = 0; i < charsSize; i++) {
        if (i + 1 < charsSize && chars[i] == chars[i + 1]) {
            count++;
        } else {
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

// test function
bool run_test(FILE *file, int test_case_num) {
    char a[1000], expected[1000], result[1000]; 
    char c;

    if (fscanf(file, "%s %c %s", a, &c, expected) != 3) {
        if (feof(file)) {
            return false;
        }
        printf("Test case %d: Error reading dataset file\n", test_case_num);
        return false;
    }


    int indicator;
    

    if (c == 'c') {
        strcpy(result, compress(a)); 
    } else {
        strcpy(result, decompress(a));
    }
    indicator = strcmp(result, expected); 
    if (indicator == 0) {
        printf("Test case %d: Passed\n", test_case_num);
        return true;
    } else {
        printf("Test case %d: Failed, expected %s, got %s\n", test_case_num, expected, result);
        return false;
    }
}



int main() {
    FILE *file = fopen("dataset.txt", "r");
    if (file == NULL) {
        perror("Error opening dataset file");
        return 1;
    }

    int test_case_num = 0;
    int passed = 0, failed = 0;

    printf("Running tests...\n");

    while (true) {
        test_case_num++;
        if (!run_test(file, test_case_num)) {
            if (feof(file)) break;
            failed++;
        } else {
            passed++;
        }
    }

    fclose(file);

    printf("\nTotal tests: %d | Passed: %d | Failed: %d\n", passed + failed, passed, failed);

    return (failed == 0) ? 0 : 1;
}
