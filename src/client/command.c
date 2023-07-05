/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** client_process.c
*/

#include "../../include/client.h"

int help_command(void)
{
    char *str = open_file("ressources/help_client.txt");

    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    } else
        printf("error: help file not found\n");
    return 0;
}

int login_command(client_t *client, char *input)
{
    if (client->auth == 1)
        printf("You are already logged in.\n");
    else if (write(client->socket, input, strlen(input)) < 0)
        return print_error_int(SEND_ERR);
    return 0;
}

int logout_command(client_t *client, char *input)
{
    if (write(client->socket, input, strlen(input)) < 0)
        return print_error_int(SEND_ERR);
    client_event_logged_out(client->user_id, client->user_name);
    return 1;
}

int users_command(client_t *client, char *input)
{
    if (write(client->socket, input, strlen(input)) < 0)
        return print_error_int(SEND_ERR);
    return 0;
}

int send_command(client_t *client, char *input)
{
    if (write(client->socket, input, strlen(input)) < 0)
        return print_error_int(SEND_ERR);
    return 0;
}
