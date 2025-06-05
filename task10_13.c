#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child: PID = %d, sleeping for 5 seconds...\n", getpid());
        sleep(5);
        printf("Child: done sleeping, exiting with code 42.\n");
        exit(42);
    } else {
        int status;
        pid_t result;

        while (1) {
            result = waitpid(pid, &status, WNOHANG);

            if (result == 0) {
                printf("Parent: child still running, doing other work...\n");
                sleep(1);
            } else if (result == -1) {
                perror("waitpid failed");
                break;
            } else {
                if (WIFEXITED(status)) {
                    printf("Parent: child exited with code %d\n", WEXITSTATUS(status));
                } else {
                    printf("Parent: child did not exit normally.\n");
                }
                break;
            }
        }
    }

    return 0;
}

