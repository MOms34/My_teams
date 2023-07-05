/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/client.h"

int print_help_client(void)
{
    printf("USAGE: ./myteams_cli ip port\n\n  \
    ip   is the server ip address on which the server socket listens.\n  \
    port is the port number on which the server socket listens\n");
    return 0;
}

int print_error_int(char *message)
{
    if (message != NULL)
        printf("%s\n", message);
    return 84;
}

int error_handling(int ac, char **argv)
{
    if (is_number_port(argv[2]) == -1) return 84;
    return 0;
}

void clean_client(client_t *client)
{
    shutdown(client->socket, SHUT_RDWR);
    free(client->ip);
    free(client);
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
