#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void ToLowerArray(char *input) {
    for (size_t i = 0; i < strlen(input); i++) {
        input[i] = tolower(input[i]);   
    }
}

int FindValidAdresses(char *input, char *founded_adress,
                      bool seen[127]) {
    /*
    This function searches for valid addresses from standard input and stores them
    in the 'founded_adress' string. It also tracks occurrences of the next character 
    in the 'seen' array and returns the count of found addresses. 
    */
    char current_adress[100];
    int count = 0;
    while (fgets(current_adress, sizeof(current_adress), stdin)) {
        ToLowerArray(current_adress);
        if (strncmp(input, current_adress, strlen(input)) == 0) {
            char last_char = current_adress[strlen(input)];
            if (!seen[(int)last_char]) {
                seen[(int)last_char] = true;
            }
            strcpy(founded_adress, current_adress);
            count++;
        }
    }
    return count;
}

void FilterEnableChars(bool seen[127], char *result) {
    unsigned char index = 0;
    for (size_t i = 32; i <= 126; i++) {
        if (seen[i]) {
            result[index] = (char)i;
            index++;
        }
    }
    result[index] = '\0';
}

int main(int argc, char *argv[]) {
    char input[100];
    if (argc == 1) {
        input[0] = '\0';
    }
    else if (argc == 2) {
        strcpy(input, argv[1]);
        ToLowerArray(input);
    }
    else {
        printf("Wrong number of arguments.\n");
        return 1;
    }

    bool seen[127] = {false}; //Every index is, if specific ASCII is enable.
    char founded_adress[100];
    int count = FindValidAdresses(input, founded_adress, seen);
    if (count == 0) {
        printf("Not found.\n");
    }
    else if (count == 1) {
        printf("FOUND: %s\n", founded_adress);
    }
    else {
        char result[94]; //126 - 32 = 94 (maximum of characters).
        FilterEnableChars(seen, result);
        printf("Enable: %s\n", result);
    }
    return 0;
}
