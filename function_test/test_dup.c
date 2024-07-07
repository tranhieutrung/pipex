#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd1, fd2, fd3;

    // Mở file1.txt để đọc
    fd1 = open("file1.txt", O_RDONLY);
    if (fd1 < 0) {
        perror("Không thể mở file1.txt");
        return 1;
    }

    // Mở file2.txt để ghi, hoặc tạo nếu chưa tồn tại
    fd2 = open("file2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 < 0) {
        perror("Không thể mở hoặc tạo file2.txt");
        close(fd1);
        return 1;
    }

	fd3 = dup(fd2);

    // Sao chép fd1 để trỏ đến cùng tập tin như fd2
    if (dup2(fd1, fd2) < 0) {
        perror("dup2 failed");
        close(fd1);
        close(fd2);
        return 1;
    }

    // Đóng fd1 sau khi đã sao chép
    // close(fd1);

    // Bây giờ fd2 trỏ đến cùng tập tin như fd1 (file1.txt)
    // Sử dụng fd2 để ghi dữ liệu vào file2.txt
    char buffer[100];
    ssize_t bytes_read;
    char path[1024];
    ssize_t nbytes;

    // Lấy PID của tiến trình hiện tại
    pid_t pid = getpid();

    // Tạo đường dẫn tới file descriptor trong /proc/<pid>/fd
    sprintf(path, "/proc/%d/fd/%d", pid, fd1);

    // Đọc liên kết tượng trưng để lấy đường dẫn
    nbytes = readlink(path, path, sizeof(path) - 1);
    if (nbytes >= 0) {
        path[nbytes] = '\0';
        printf("fd1 đang trỏ đến: %s\n", path);
    } else {
        perror("readlink failed");
    }

    // Lấy PID của tiến trình hiện tại
    pid = getpid();

    // Tạo đường dẫn tới file descriptor trong /proc/<pid>/fd
    sprintf(path, "/proc/%d/fd/%d", pid, fd2);

    // Đọc liên kết tượng trưng để lấy đường dẫn
    nbytes = readlink(path, path, sizeof(path) - 1);
    if (nbytes >= 0) {
        path[nbytes] = '\0';
        printf("fd2 đang trỏ đến: %s\n", path);
    } else {
        perror("readlink failed");
    }

    // Lấy PID của tiến trình hiện tại
    pid = getpid();

    // Tạo đường dẫn tới file descriptor trong /proc/<pid>/fd
    sprintf(path, "/proc/%d/fd/%d", pid, fd3);

    // Đọc liên kết tượng trưng để lấy đường dẫn
    nbytes = readlink(path, path, sizeof(path) - 1);
    if (nbytes >= 0) {
        path[nbytes] = '\0';
        printf("fd3 đang trỏ đến: %s\n", path);
    } else {
        perror("readlink failed");
    }
    // Đọc từ fd3 (file1.txt) và ghi vào fd2 (file2.txt)
    while ((bytes_read = read(fd2, buffer, sizeof(buffer))) > 0)
    {
        // Lấy đường dẫn tập tin được mở bởi fd2
        if (write(fd3, buffer, bytes_read) != bytes_read) {
            perror("write error");
            close(fd1);
            close(fd2);
            close(fd3);
            return 1;
        }
        printf("Copied content of file1 to file2\n");
    }

    close(fd1);
    close(fd2);
    close(fd3);
    return 0;
}
