/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/server.h"

char one_or_zero(int nb)
{
    if (nb == 1)
        return '1';
    return '0';
}

int users_command(client_t **client, int ic)
{
    char *resp = NULL;
    int size = 0;

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (client[i]->socket != 0) {
            size = strlen(client[i]->name) + strlen(client[i]->uuid) + 6;
            resp = malloc(sizeof(char) * (size + 1));
            snprintf(resp, size, "b-%s|%s|%c|", client[i]->name,
            client[i]->uuid, one_or_zero(client[i]->auth));
            write(client[ic]->socket, resp, strlen(resp));
            free(resp);
        }
    }
    return 0;
}

void print_user_info(client_t **client, int ic)
{
    char *resp = NULL;
    int size = 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client[i]->socket != 0 &&
        strcmp(client[ic]->argument[0], client[i]->uuid) == 0) {
            size = strlen(client[i]->name) + strlen(client[i]->uuid) + 6;
            resp = malloc(sizeof(char) * (size + 1));
            snprintf(resp, size, "d-%s|%s|%c|", client[i]->name,
            client[i]->uuid, one_or_zero(client[i]->auth));
            write(client[ic]->socket, resp, strlen(resp));
            free(resp);
            break;
        }
    }
}
