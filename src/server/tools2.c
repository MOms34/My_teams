/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/server.h"

char *fuck_coding_style(char *d_name, int *i)
{
    char *file = malloc(sizeof(char) * (strlen(d_name) + 1));

    strcpy(file, d_name);
    ++(*i);
    return file;
}

char **get_directory_files(char *path)
{
    DIR *dir;
    struct dirent *ent;
    char **files = NULL;
    int len = 0;
    int i = 0;

    dir = opendir(path);
    if (dir == NULL) return NULL;
    while ((ent = readdir(dir)) != NULL)
        if (ent->d_type == DT_REG)
            len++;
    rewinddir(dir);
    files = malloc(sizeof(char *) * (len + 1));
    while ((ent = readdir(dir)) != NULL)
        if (ent->d_type == DT_REG)
            files[i] = fuck_coding_style(ent->d_name, &i);
    files[len] = NULL;
    closedir(dir);
    return files;
}

char *open_file(char *path)
{
    int fd = 0;
    char *str = NULL;
    struct stat statbuf;

    stat(path, &statbuf);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return NULL;
    str = malloc(sizeof(char) * (statbuf.st_size + 1));
    read(fd, str, statbuf.st_size);
    close(fd);
    return str;
}

char *get_user(char *user_name)
{
    int size = strlen(user_name) - 3;
    char *user = malloc(sizeof(char) * size);

    for (int i = 0; i < (size - 1); ++i)
        user[i] = user_name[i];
    user[size - 1] = '\0';
    return user;
}

char *replace_char(char *s1, char *s2, char *s3)
{
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);
    int s3_len = strlen(s3);
    char *result = malloc(sizeof(char) * (s1_len + 1));
    char *p = s1;
    char *q = result;

    while (*p) {
        if (strstr(p, s2) == p) {
            strcpy(q, s3);
            p += s2_len;
            q += s3_len;
        } else {
            *q++ = *p++;
        }
    }
    *q = '\0';
    return result;
}
