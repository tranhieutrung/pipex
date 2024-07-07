#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[1024];
    ssize_t nbytes;

// pipefd[0] được sử dụng để đọc dữ liệu từ pipe.
// pipefd[1] được sử dụng để ghi dữ liệu vào pipe.

    // Tạo pipe va ghi vao pipefd
//     pipe(pipefd) tạo ra một vùng đệm và gán hai file descriptor pipefd[0] và pipefd[1].
// pipefd[0] dùng để đọc từ vùng đệm.
// pipefd[1] dùng để ghi vào vùng đệm.
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Tạo một tiến trình con
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Quá trình con

        // Đóng phần đọc của pipe
        close(pipefd[0]);

        // Ghi dữ liệu vào pipe
        char *message = "Hello from child process!\n";
        write(pipefd[1], message, strlen(message));
        close(pipefd[1]);

        exit(EXIT_SUCCESS);
    } else {
        // Quá trình cha

        // Đóng phần ghi của pipe
        close(pipefd[1]);

        // Đọc dữ liệu từ pipe
        nbytes = read(pipefd[0], buffer, sizeof(buffer));
        close(pipefd[0]);

        printf("Received message in parent process: %s", buffer);
    }

    return 0;
}
