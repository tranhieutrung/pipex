#include <unistd.h>
#include <stdio.h> // Thêm tệp tiêu đề này để khai báo hàm perror

int main() {
    char *args[] = {"/bin/ls", "-l", NULL};
    char *env[] = {NULL};
    
    execve("/bin/ls", args, env);
    
    // Nếu execve thành công, đoạn mã dưới đây sẽ không được thực thi
    perror("execve failed");
    return 1;
}
