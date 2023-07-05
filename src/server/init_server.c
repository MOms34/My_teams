/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/server.h"

server_t *init_server(int port)
{
    server_t *server = malloc(sizeof(server_t));

    server->data_socket = 0;
    server->nbClients = 0;
    server->control_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->control_socket == -1)
        return print_error_server("Unable to create the server socket");
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(port);
    if (bind(server->control_socket, (struct sockaddr *)&server->address,
    sizeof(server->address)) < 0)
        return print_error_server("Unable to bind the server socket");
    if (listen(server->control_socket, 200) < 0)
        return print_error_server("Unable to listen to incoming connections");
    return server;
}

void load_info_client(client_t *client, char *token, int wich)
{
    token = strtok(NULL, ": ");
    token[strcspn(token, "\n")] = '\0';
    if (wich == 0) {
        client->name = malloc(sizeof(char) * MAX_NAME_LENGTH);
        strncpy(client->name, token, MAX_NAME_LENGTH);
    } else {
        client->uuid = malloc(sizeof(char) * 37);
        strncpy(client->uuid, token, 37);
    }
}

void set_info_client(client_t *client, char *user_name)
{
    char *path = malloc(sizeof(char) * (strlen(user_name) + 20));
    FILE *file = NULL;
    char *token = NULL;
    char line[256];

    sprintf(path, "save/users/%s", user_name);
    file = fopen(path, "r");
    while (fgets(line, sizeof(line), file) != NULL) {
        token = strtok(line, ": ");
        if (strcmp(token, "user_name") == 0)
            load_info_client(client, token, 0);
        if (strcmp(token, "uuid") == 0)
            load_info_client(client, token, 1);
    }
    fclose(file);
    free(path);
    server_event_user_loaded(client->uuid, client->name);
}

client_t **init_client_struct(server_t *server)
{
    client_t **client = malloc(sizeof(client_t *) * MAX_CLIENTS);
    char **users = get_directory_files("save/users");
    int nb_users = count_array(users);

    for (int i = 0; i < MAX_CLIENTS; i++, nb_users--) {
        client[i] = malloc(sizeof(client_t));
        client[i]->socket = 0;
        client[i]->auth = 0;
        if (nb_users > 0 && users[i] != NULL) {
            set_info_client(client[i], users[i]);
            client[i]->socket = -1;
            server->nbClients++;
        }
    }
    return client;
}
