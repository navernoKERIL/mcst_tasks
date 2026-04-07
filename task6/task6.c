#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Проверяем аргументы
    if (argc != 2){
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    struct stat st;

    // Вызываем stat
    if (stat(path, &st) == -1){
        perror("stat");
        return 1;
    }

    printf("File: %s\n", path);
    printf("Size: %ld\n", st.st_size);
    printf("Blocks: %ld\n", st.st_blocks);
    
    // Опредляем тип файла
    if (S_ISREG(st.st_mode))
        printf("Type: regular file\n");
    else if (S_ISDIR(st.st_mode))
        printf("Type: directory\n");
    else if (S_ISLNK(st.st_mode))
        printf("Type: symbolic link\n");
    else
        printf("Type: other\n");
    
    printf("Uid: %d\n", st.st_uid);
    printf("Gid: %d\n", st.st_gid);
    
    return 0;
}