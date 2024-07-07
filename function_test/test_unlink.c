#include <stdio.h>
#include <unistd.h>

int main() {
    const char *file_path = "test.txt";

    // Tạo một file để thử nghiệm
    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        perror("Không thể tạo file");
        return 1;
    }
    fclose(file);

    // Xóa file sử dụng unlink
    if (unlink(file_path) == 0) {
        printf("File '%s' đã bị xóa thành công.\n", file_path);
    } else {
        perror("Lỗi khi xóa file");
    }

    return 0;
}
