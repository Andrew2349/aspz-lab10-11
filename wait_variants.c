#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        sleep(2);
        exit(7);
    } else {
        int status;
        pid_t res = waitpid(pid, &status, WNOHANG);
        if (res == 0) {
            printf("Child not finished yet (non-blocking)\n");
            sleep(3);
            waitpid(pid, &status, 0);
        }
        if (WIFEXITED(status)) {
            printf("Child exited with code %d\n", WEXITSTATUS(status));
        }
    }
    return 0;
}
