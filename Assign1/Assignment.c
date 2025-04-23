#include <stdio.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <stdlib.h>

int main() { 
    int pid; 
    int ppid;
    int fork_var;
    int ch;

    pid = getpid(); 
    ppid = getppid();

    printf("You are in a Parent Process\n"); 
    printf("The PID of this process is %d\n", pid); 
    printf("The PID of parent process is %d\n", ppid);

    do {
        printf("\nYou are welcome!!!\nChoose any one option:\n");
        printf("1. GREP Command\n2. CP Command\n3. Exit\n");
        printf("Enter your choice: "); 
        scanf("%d", &ch);

        switch(ch) { 
            case 1: {
                fork_var = fork();
                if (fork_var == 0) {
                    printf("You are in a child process.\n"); 
                    pid = getpid();
                    ppid = getppid();
                    printf("The PID of child process is %d\n", pid); 
                    printf("The PID of parent process is %d\n", ppid); 
                    char pat[10];
                    char fl[10];
                    printf("Enter a file name: "); 
                    scanf("%s", fl);
                    printf("Enter a pattern: "); 
                    scanf("%s", pat);
                    printf("Running GREP command:\n"); 
                    execlp("./122B1B235_grep", "122B1B235_grep", pat, fl, NULL); 
                    exit(1);
                } else if (fork_var > 0) { 
                    wait(NULL);
                } else {
                    perror("Fork failed");
                }
                break;
            }

            case 2: {
                fork_var = fork();
                if (fork_var == 0) {
                    printf("You are in a child process.\n"); 
                    pid = getpid();
                    ppid = getppid();
                    printf("The PID of child process is %d\n", pid); 
                    printf("The PID of parent process is %d\n", ppid); 
                    char fl1[10];
                    char fl2[10];
                    printf("Enter a source file name: "); 
                    scanf("%s", fl1);
                    printf("Enter a destination file name: "); 
                    scanf("%s", fl2);
                    printf("Running CP command:\n"); 
                    execlp("./122B1B235_cp", "122B1B235_cp", fl1, fl2, NULL); 
                    exit(1);
                } else if (fork_var > 0) { 
                    wait(NULL);
                } else {
                    perror("Fork failed");
                }
                break;
            }

            case 3: {
                printf("Thank you!!!\n"); 
                exit(1);
            }

            default: {
                printf("You entered wrong option!!! Please try again.\n"); 
                break;
            }
        }
    } while(ch != 3);

    return 0;
}
