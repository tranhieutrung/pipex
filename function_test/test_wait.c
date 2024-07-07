#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Tiến trình con
        printf("Child process\n");
        sleep(2);  // Giả lập công việc của tiến trình con
        exit(EXIT_SUCCESS);
    } else {
        // Tiến trình cha
        int status;
        pid_t wpid = waitpid(pid, &status, 0);
        if (wpid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }

		status;
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}

// pid: PID của tiến trình con mà bạn muốn chờ đợi. Có thể sử dụng các giá trị đặc biệt:

// -1: Chờ bất kỳ tiến trình con nào.
// > 0: Chờ tiến trình con có PID cụ thể.
// 0: Chờ bất kỳ tiến trình con nào có cùng nhóm tiến trình với tiến trình cha.
// < -1: Chờ bất kỳ tiến trình con nào có nhóm tiến trình bằng |pid|.
// status: Con trỏ tới biến nguyên mà hàm sẽ lưu trữ trạng thái của tiến trình con khi nó kết thúc. Nếu không quan tâm đến trạng thái, bạn có thể truyền vào NULL.

// options: Tùy chọn, có thể là 0 hoặc kết hợp các cờ như WNOHANG (không chờ đợi nếu không có tiến trình nào kết thúc).

// Trả về PID của tiến trình con đã kết thúc hoặc -1 nếu có lỗi.