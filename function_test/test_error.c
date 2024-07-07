#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    FILE *file;

    // Cố gắng mở một file không tồn tại để gây ra lỗi
    file = fopen("nonexistent.txt", "r");
    if (file == NULL) {
        // Sử dụng strerror để hiển thị thông báo lỗi
        printf("Lỗi khi mở file (strerror): %s\n", strerror(errno));
		perror("Lỗi khi mở file (perror)");

    }

    return 0;
}
