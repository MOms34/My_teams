/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/server.h"

void create_info_client(client_t *client, char *user_name)
{
    char *path = malloc(sizeof(char) * (strlen(user_name) + 20));
    char *uuid = generate_uuid();
    char *user_name_f = get_user(user_name);
    FILE *file = NULL;

    sprintf(path, "save/users/%s", user_name);
    file = fopen(path, "w");
    fprintf(file, "user_name: %s\nuuid: %s\n\n", user_name_f, uuid);
    fclose(file);
    client->name = user_name_f;
    client->uuid = uuid;
    client->auth = 1;
    free(path);
    server_event_user_created(client->uuid, client->name);
}

void login_response(client_t *client, int found)
{
    int size = 0;
    char *resp = NULL;

    if (found != -1) {
        size = strlen(client->uuid) + strlen(client->name) + 4;
        resp = malloc(sizeof(char) * (size + 1));
        snprintf(resp, size, "a-%s|%s|", client->name, client->uuid);
        resp[size] = '\0';
        write(client->socket, resp, strlen(resp));
        free(resp);
    }
}

void bind_with_existing_client(client_t **client, int *ic, char *user,
int *found)
{
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (client[i]->socket != 0 && strcmp(client[i]->name, user) == 0
        && client[i]->auth == 0) {
            client[i]->socket = client[*ic]->socket;
            client[i]->address = client[*ic]->address;
            client[i]->auth = 1;
            client[*ic]->socket = 0;
            *ic = i;
            return;
        }
    }
    *found = -1;
}

int login_command(client_t **client, int ic)
{
    char *user_name = malloc(sizeof(char) *
    (strlen(client[ic]->argument[0]) + 5));
    char **users = get_directory_files("save/users");
    int found = 0;
    int new_ic = ic;

    snprintf(user_name, strlen(client[ic]->argument[0]) + 5, "%s.txt",
    client[ic]->argument[0]);
    for (int i = 0; users[i] != NULL; ++i)
        if (strcmp(users[i], user_name) == 0) found = 1;
    if (found == 1)
        bind_with_existing_client(client, &new_ic,
        client[ic]->argument[0], &found);
    else
        create_info_client(client[ic], user_name);
    login_response(client[new_ic], found);
    if (found != -1)
        server_event_user_logged_in(client[new_ic]->uuid);
    return 0;
}
