/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** client_process.c
*/

#include "../../include/client.h"

fd_set listen_activity(client_t *client, int *maxfd, struct timeval *timeout)
{
    fd_set fds;

    FD_ZERO(&fds);
    FD_SET(client->socket, &fds);
    *maxfd = client->socket;
    FD_SET(STDIN_FILENO, &fds);
    if (STDIN_FILENO > *maxfd)
        *maxfd = STDIN_FILENO;
    timeout->tv_sec = 0.5;
    timeout->tv_usec = 0;
    return fds;
}

void treatment_resp(client_t *client, char *resp)
{
    if (strncmp(resp, "a-", 2) == 0) return login_resp(client, resp);
    if (strncmp(resp, "b-", 2) == 0) return users_resp(client, resp);
    if (strncmp(resp, "c-", 2) == 0) return send_resp(client, resp);
    if (strncmp(resp, "d-", 2) == 0) return user_resp(client, resp);
}

int activity_server_socket(client_t *client, fd_set fds)
{
    char buffer[BUFFER_SIZE];

    if (FD_ISSET(client->socket, &fds)) {
        FD_ZERO(&client->read_fds);
        FD_SET(client->socket, &client->read_fds);
        client->max_fd = client->socket;
        if (FD_ISSET(client->socket, &client->read_fds)) {
            bzero(buffer, BUFFER_SIZE);
            read(client->socket, buffer, BUFFER_SIZE);
            treatment_resp(client, buffer);
        }
    }
    return 0;
}
