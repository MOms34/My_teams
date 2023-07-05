/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/server.h"

server_t *print_error_server(char *message)
{
    if (message != NULL)
        printf("%s\n", message);
    return NULL;
}

int print_error_int(char *message)
{
    if (message != NULL)
        printf("%s\n", message);
    return 84;
}

int print_help(void)
{
    printf("USAGE: ./myteams_server port\n\n  \
    port is the port number on which the server socket listens.\n");
    return 0;
}

int error_handling(int ac, char **argv)
{
    if (is_number_port(argv[1]) == -1)
        return 84;
    return 0;
}

char *generate_uuid(void)
{
    uuid_t uuid;
    char *str = malloc(sizeof(char) * 37);

    uuid_generate_random(uuid);
    uuid_unparse(uuid, str);
    return str;
}
