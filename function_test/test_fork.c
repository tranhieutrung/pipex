#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        // Không thể tạo quá trình con
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Quá trình con
        printf("Hello from child process!\n");
    } else {
        // Quá trình cha
        printf("Hello from parent process! Child PID: %d\n", pid);
    }

    return 0;
}

// getpid: Trả về PID của quá trình hiện tại (quá trình con).
// getppid: Trả về PID của quá trình cha.
