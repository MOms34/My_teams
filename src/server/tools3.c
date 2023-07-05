/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/server.h"

char *find_uuid(client_t *client, char *token)
{
    char *uuid = NULL;

    if (strcmp(token, "uuid") == 0) {
        token = strtok(NULL, ": ");
        token[strcspn(token, "\n")] = '\0';
        uuid = strdup(token);
    }
    return uuid;
}

char *loop(client_t *client, char *path)
{
    FILE *file = fopen(path, "r");
    char *token = NULL;
    char *uuid = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        token = strtok(line, ": ");
        if ((uuid = find_uuid(client, token)) != NULL)
            break;
    }
    fclose(file);
    return uuid;
}

char *who_is_this_uuid(client_t *client)
{
    char **users = get_directory_files("save/users");
    char *path = NULL;
    char *uuid = NULL;

    for (int i = 0; users[i] != NULL; i++) {
        path = malloc(sizeof(char) * (strlen(users[i]) + 12));
        sprintf(path, "save/users/%s", users[i]);
        uuid = loop(client, path);
        free(path);
        if (uuid != NULL && strcmp(uuid, client->argument[0]) == 0)
            return users[i];
    }
    return NULL;
}

bool is_conversation_exist(client_t *client, char *path)
{
    char *file = open_file(path);
    char *flag = malloc(sizeof(char) * (strlen(client->uuid) + 3));

    snprintf(flag, strlen(client->uuid) + 2, "[%s]", client->uuid);
    flag[strlen(client->uuid) + 2] = '\0';
    if (strstr(file, flag) != NULL) {
        free(file);
        free(flag);
        return true;
    }
    free(file);
    free(flag);
    return false;
}

int is_connecting_dest(client_t **client, char *dest_uuid)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (client[i]->auth == 1 && strcmp(client[i]->uuid, dest_uuid) == 0)
            return i;
    return -1;
}
