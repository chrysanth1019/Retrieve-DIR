#include <stdio.h>
#include <unistd.h>
#include <limits.h>

void print_file_path(FILE *fp) {
    int fd = fileno(fp); // Get the file descriptor
    if (fd == -1) {
        perror("fileno");
        return;
    }

    char path[PATH_MAX];
    snprintf(path, sizeof(path), "/proc/self/fd/%d", fd);

    char actualpath[PATH_MAX];
    if (readlink(path, actualpath, sizeof(actualpath)) != -1) {
        printf("File Path: %s\n", actualpath);
    } else {
        perror("readlink");
    }
}

int main() {
    FILE *fp = fopen("main.c", "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    print_file_path(fp);

    fclose(fp);
    return 0;
}