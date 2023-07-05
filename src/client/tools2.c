/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/client.h"

// char *fuck_coding_style(char *d_name, int *i)
// {
//     char *file = malloc(sizeof(char) * (strlen(d_name) + 1));

//     strcpy(file, d_name);
//     ++(*i);
//     return file;
// }

// char **get_directory_files(char *path)
// {
//     DIR *dir;
//     struct dirent *ent;
//     char **files = NULL;
//     int len = 0;
//     int i = 0;

//     dir = opendir(path);
//     if (dir == NULL) return NULL;
//     while ((ent = readdir(dir)) != NULL)
//         if (ent->d_type == DT_REG)
//             len++;
//     rewinddir(dir);
//     files = malloc(sizeof(char *) * (len + 1));
//     while ((ent = readdir(dir)) != NULL)
//         if (ent->d_type == DT_REG)
//             files[i] = fuck_coding_style(ent->d_name, &i);
//     files[len] = NULL;
//     closedir(dir);
//     return files;
// }

// char *format_user_name(char *input)
// {
//     char *user_name = NULL;
//     char *output = NULL;
//     int len = 0;

//     input[strlen(input) - 1] = '\0';
//     user_name = strchr(input, ' ');
//     if (user_name == NULL) return NULL;
//     user_name += 2;
//     user_name[strlen(user_name) - 1] = '\0';
//     len = strlen(user_name) + strlen(".txt") + 1;
//     output = malloc(len * sizeof(char));
//     snprintf(output, len, "%s.txt", user_name);
//     return output;
// }
