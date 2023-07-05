/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/server.h"

int logout_command(client_t *client, server_t *server, int i)
{
    close(client->socket);
    client->socket = -1;
    client->auth = 0;
    client->nb_arg = 0;
    if (i == 1)
        server_event_user_logged_out(client->uuid);
    return 0;
}
