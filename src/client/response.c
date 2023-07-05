/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** client_process.c
*/

#include "../../include/client.h"

void login_resp(client_t *client, char *resp)
{
    char *token = NULL;

    resp += 2;
    token = strtok(resp, "|");
    for (int i = 0; token != NULL; ++i) {
        if (i == 0)
            client->user_name = strdup(token);
        if (i == 1)
            client->user_id = strdup(token);
        token = strtok(NULL, "|");
    }
    client->auth = 1;
    client_event_logged_in(client->user_id, client->user_name);
}

void users_resp(client_t *client, char *resp)
{
    char *token = NULL;
    char *uuid = NULL;
    char *name = NULL;
    int auth = 0;

    resp += 2;
    token = strtok(resp, "|");
    for (int i = 0; token != NULL; ++i) {
        if (i == 0)
            uuid = strdup(token);
        if (i == 1)
            name = strdup(token);
        if (i == 2)
            auth = atoi(token);
        token = strtok(NULL, "|");
    }
    client_print_users(uuid, name, auth);
}

void send_resp(client_t *client, char *resp)
{
    char *token = NULL;
    int index = 0;
    int error = 0;
    char *uuid = NULL;

    resp += 2;
    token = strtok(resp, "|");
    while (token != NULL) {
        if (index == 1 && error == 1)
            client_error_unknown_user(token);
        if (index == 1 && error == 0)
            client_event_private_message_received(uuid, token);
        if (index == 0 && strncmp(token, "error", 5) == 0)
            error = 1;
        else
            uuid = strdup(token);
        token = strtok(NULL, "|");
        index++;
    }
}

void user_resp(client_t *client, char *resp)
{
    char *token = NULL;
    char *uuid = NULL;
    char *name = NULL;
    int auth = 0;

    resp += 2;
    token = strtok(resp, "|");
    for (int i = 0; token != NULL; ++i) {
        if (i == 0)
            uuid = strdup(token);
        if (i == 1)
            name = strdup(token);
        if (i == 2)
            auth = atoi(token);
        token = strtok(NULL, "|");
    }
    client_print_user(uuid, name, auth);
}
