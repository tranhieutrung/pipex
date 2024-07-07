#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[1024];
    ssize_t nbytes;
    const char *file_path = "tempfile.txt";

    // Tạo một file tạm để thử nghiệm unlink
    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        perror("Không thể tạo file");
        return 1;
    }
    fprintf(file, "Temporary file content.\n");
    fclose(file);

    // Tạo pipe
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
        if (write(pipefd[1], message, strlen(message)) == -1) {
            perror("write");
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);

        // Xóa file tạm
        if (unlink(file_path) == 0) {
            printf("Child process: File '%s' đã bị xóa thành công.\n", file_path);
        } else {
            perror("Child process: Lỗi khi xóa file");
        }

        exit(EXIT_SUCCESS);
    } else {
        // Quá trình cha

        // Đóng phần ghi của pipe
        close(pipefd[1]);

        // Đọc dữ liệu từ pipe
        nbytes = read(pipefd[0], buffer, sizeof(buffer));
        if (nbytes == -1) {
            perror("read");
            close(pipefd[0]);
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);

        // In ra thông báo nhận được
        printf("Parent process: Received message: %.*s", (int)nbytes, buffer);
    }

    return 0;
}
