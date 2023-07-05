/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/server.h"

int setup_socket(server_t *server, client_t **client)
{
    FD_ZERO(&server->read_fds);
    FD_SET(server->control_socket, &server->read_fds);
    server->max_fd = server->control_socket;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client[i]->nb_arg = 0;
        client[i]->argument = NULL;
        if (client[i]->socket > 0)
            FD_SET(client[i]->socket, &server->read_fds);
        if (client[i]->socket > server->max_fd)
            server->max_fd = client[i]->socket;
    }
    server->activity = select(server->max_fd + 1, &server->read_fds,
    NULL, NULL, NULL);
    if ((server->activity < 0) && (errno != EINTR))
        return print_error_int(ACTIVITY_ERR);
    return 0;
}

int check_new_client(server_t *server, client_t **client)
{
    int new_socket;
    struct sockaddr_in new_address;
    int address_len = sizeof(new_address);

    new_socket = accept(server->control_socket,
    (struct sockaddr *) &new_address, (socklen_t *) &address_len);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client[i]->socket == 0) {
            client[i]->socket = new_socket;
            client[i]->address = new_address;
            client[i]->auth = 0;
            break;
        }
    }
    return 0;
}

int activity_client_socket(server_t *server, client_t **client)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (FD_ISSET(client[i]->socket, &server->read_fds) &&
        client_command(server, client, i) == 84)
            return 84;
        else
            client[i]->id = i;
    }
    return 0;
}

int client_command(server_t *server, client_t **client, int i)
{
    char buffer[BUFFER_SIZE];

    bzero(buffer, BUFFER_SIZE);
    if (read(client[i]->socket, buffer, BUFFER_SIZE) == 0)
        return logout_command(client[i], server, 0);
    if (buffer[0] == '\r' || buffer[0] == '\n') return 0;
    buffer[strlen(buffer) - 1] = '\0';
    client[i]->buff_temp = malloc(sizeof(char) * BUFFER_SIZE);
    strcpy(client[i]->buff_temp, buffer);
    parse_cmd(buffer, client[i], 0);
    if (remove_quotes(client[i]) == -1 || check_cmd(server, client, i) == -1)
        dprintf(client[i]->socket, "Please enter a valid cmd\n");
    return 0;
}
