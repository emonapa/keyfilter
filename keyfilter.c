#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#define MAX_LEN 100

void ToUpperArray(char *input) {
    for (size_t i = 0; i < strlen(input); i++) {
        input[i] = toupper(input[i]);   
    }
}

int FindValidAdresses(char *input, char founded_adress[MAX_LEN + 1],
                      bool seen[127]) {
    /*
    This function searches for valid addresses from stdin and stores them
    in the 'founded_adress' string. It also tracks occurrences of the next character 
    in the 'seen' array and returns the count of found addresses. 
    */
    char current_adress[MAX_LEN + 1];
    int count = 0;
    while (fgets(current_adress, MAX_LEN + 1, stdin)) {
        //Handling maximum characters in line.  
        if (strlen(current_adress) == MAX_LEN && current_adress[MAX_LEN] != '\n') {
            current_adress[MAX_LEN] = '\0';
            //Ignore next chars.
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        } 
        else {  
            current_adress[strlen(current_adress) - 1] = '\0';
        }

        ToUpperArray(current_adress);
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
    char input[MAX_LEN + 1];
    if (argc == 1) {
        input[0] = '\0'; //Special case where len of input == 0.
    }
    else if (argc == 2) {
        strncpy(input, argv[1], MAX_LEN + 1);
        ToUpperArray(input);
    }
    else {
        printf("Wrong number of arguments.\n");
        return 1;
    }

    bool seen[127] = {false}; //Every index is, if specific ASCII is enable.
    char founded_adress[MAX_LEN + 1];
    int count = FindValidAdresses(input, founded_adress, seen);
    if (count == 0) {
        printf("Not found.\n");
    }
    else if (count == 1) {
        printf("Found: %s\n", founded_adress);
    }
    else {
        char result[95]; //126 - 32 + 1 NULL BYTE = 95 (maximum of characters).
        FilterEnableChars(seen, result);
        printf("Enable: %s\n", result);
    }
    return 0;
}
