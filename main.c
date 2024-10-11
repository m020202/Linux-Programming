#include <dirent.h>
#include <printf.h>
#include <unistd.h>

void my_pwd(void);

int main() {
    my_pwd();
}

void my_pwd(void){
    char dirname[200];
    if (getcwd(dirname, 200) == NULL) {
        perror("getcwd error");
    }
    else
        printf("%s\n", dirname);
}