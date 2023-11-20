#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = getpid(); // get process id
    pid_t ppid = getppid(); // get parent process id

    printf("Current Process ID: %d\n", pid);
    printf("Parent Process ID: %d\n", ppid);

    return 0;
}