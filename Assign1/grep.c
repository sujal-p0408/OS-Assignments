#include <stdio.h> 
#include <string.h>

int main(int argc, char* argv[]) { 
    if (argc != 3) {
        printf("You cannot enter more or less than 3 arguments.\n"); 
        return 0;
    }

    char* pat = argv[1]; 
    char* fn = argv[2]; 
    char line[5000];

    FILE* fp = fopen(fn, "r");
    if (fp == NULL) {
        perror("Error opening file"); 
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) { 
        char* match = strstr(line, pat);
        if (match) {
            *match = '\0'; 
            printf("%s", line);                    // print before match
            printf("\033[31m%s\033[0m", pat);      // print matched part in red
            printf("%s", match + strlen(pat));     // print after match
        }
    }

    fclose(fp); 
    return 0;
}
