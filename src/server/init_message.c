/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/server.h"

void init_message_suite(client_t *client, message_t *mess)
{
    mess->dest_path = malloc(sizeof(char) * (strlen(mess->dest_name) + 17));
    snprintf(mess->dest_path, strlen(mess->dest_name) + 16,
    "save/users/%s.txt", mess->dest_name);
    mess->dest_path[strlen(mess->dest_name) + 16] = '\0';
    mess->cli_uuid = malloc(sizeof(char) * (strlen(client->uuid) + 4));
    snprintf(mess->cli_uuid, strlen(client->uuid) + 3, "[%s]", client->uuid);
    mess->cli_uuid[strlen(client->uuid) + 3] = '\0';
    mess->cli_path = malloc(sizeof(char) * (strlen(client->name) + 17));
    snprintf(mess->cli_path, strlen(client->name) + 16, "save/users/%s.txt",
    client->name);
    mess->cli_path[strlen(client->name) + 16] = '\0';
}

message_t *init_message(client_t *client)
{
    message_t *mess = malloc(sizeof(message_t));
    char *dest = who_is_this_uuid(client);

    if (dest == NULL) return NULL;
    mess->dest_name = get_user(dest);
    mess->dest_uuid = malloc(sizeof(char) * (strlen(client->argument[0]) + 4));
    snprintf(mess->dest_uuid, strlen(client->argument[0]) + 3, "[%s]",
    client->argument[0]);
    mess->dest_uuid[strlen(client->argument[0]) + 3] = '\0';
    init_message_suite(client, mess);
    return mess;
}

void free_message(message_t *mess)
{
    if (mess != NULL) {
        free(mess->dest_name);
        free(mess->dest_uuid);
        free(mess->dest_path);
        free(mess->cli_uuid);
        free(mess->cli_path);
        free(mess);
    }
}
