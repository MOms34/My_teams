/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** init_client.c
*/

#include "../../include/client.h"

client_t *init_client(char *ip, int port)
{
    client_t *client = malloc(sizeof(client_t));

    client->ip = malloc(sizeof(char) * (strlen(ip) + 1));
    strcpy(client->ip, ip);
    client->port = port;
    client->auth = 0;
    client->user_name = NULL;
    client->user_id = NULL;
    client->socket = socket(AF_INET, SOCK_STREAM, 0);
    client->address.sin_family = AF_INET;
    client->address.sin_port = htons(port);
    client->address.sin_addr.s_addr = inet_addr(ip);
    if (connect(client->socket, (struct sockaddr *)&client->address,
    sizeof(client->address)) == -1) {
        printf("Connection failed.\n");
        return NULL;
    }
    return client;
}
