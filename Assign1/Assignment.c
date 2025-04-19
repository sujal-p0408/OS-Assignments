#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#ifdef __unix__
#include <sys/wait.h>
#else
#include <process.h>
#endif

int main() {
    int ch;

    do {
        printf("\nMenu:\n");
        printf("1. Run CP command (copy files using child process)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: {
                int fork_var = fork();

                if (fork_var == 0) {  // Child process
                    int pid = getpid();
                    int ppid = getppid();

                    printf("The PID of child process is %d\n", pid);
                    printf("The PID of parent process is %d\n", ppid);

                    char fl1[100], fl2[100];
                    printf("Enter a source file name: ");
                    scanf("%s", fl1);
                    printf("Enter a destination file name: ");
                    scanf("%s", fl2);

                    printf("Running CP command:\n");
                    execlp("./122B1B235_cp", "122B1B235_cp", fl1, fl2, NULL);
                    
                    // If execlp fails
                    perror("execlp failed");
                    exit(1);
                } else if (fork_var > 0) {  // Parent process
                    wait(NULL);
                } else {
                    perror("Fork failed");
                }
                break;
            }

            case 3: {
                printf("Thank you!!!\n");
                exit(0);
            }

            default: {
                printf("You entered wrong option!!! Please try again.\n");
                break;
            }
        }
    } while (ch != 3);

    return 0;
}
