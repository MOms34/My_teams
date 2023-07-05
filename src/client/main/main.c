/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "../../../include/client.h"

void reset_fds(client_t *client, fd_set *fds, struct timeval *timeout)
{
    FD_ZERO(fds);
    FD_SET(client->socket, fds);
    FD_SET(STDIN_FILENO, fds);
    timeout->tv_sec = 0.5;
    timeout->tv_usec = 0;
}

int start_client(char *ip, int port)
{
    client_t *client;
    fd_set fds;
    int maxfd = 0;
    struct timeval timeout;
    char *input = NULL;
    int command = 0;

    if ((client = init_client(ip, port)) == NULL) return 84;
    fds = listen_activity(client, &maxfd, &timeout);
    while (1) {
        select(maxfd + 1, &fds, NULL, NULL, &timeout);
        if (activity_server_socket(client, fds) == 84) return 84;
        input = get_input(client, fds);
        command = treatment_input(client, input);
        if (command == 84) return 84;
        if (command == 1) break;
        reset_fds(client, &fds, &timeout);
    }
    clean_client(client);
    return 0;
}

int main(int ac, char **argv)
{
    if (ac == 2 && strcmp(argv[1], "-help") == 0) return print_help_client();
    if (ac != 3 || error_handling(ac, argv) != 0) return 84;
    return start_client(argv[1], atoi(argv[2]));
}
