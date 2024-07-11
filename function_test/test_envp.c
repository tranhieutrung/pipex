#include <stdio.h>

void print_environment_variables(char **envp) {
    // Kiểm tra nếu envp không null
    if (envp == NULL) {
        printf("No environment variables found.\n");
        return;
    }

    // Duyệt qua tất cả các biến môi trường
    for (int i = 0; envp[i] != NULL; i++) {
        printf("%s\n", envp[i]);
    }
}

int main(int argc, char **argv, char **envp) {
    // Gọi hàm để in ra các biến môi trường
    print_environment_variables(envp);
    return 0;
}
