/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "../../../include/server.h"

int start_server(int port)
{
    server_t *server;
    client_t **client;

    if ((server = init_server(port)) == NULL) return 84;
    client = init_client_struct(server);
    while (1) {
        if (setup_socket(server, client) == 84) return 84;
        if (FD_ISSET(server->control_socket, &server->read_fds) &&
        check_new_client(server, client) == 84)
            return 84;
        if (activity_client_socket(server, client) == 84)
            return 84;
    }
    return 0;
}

int main(int ac, char **argv)
{
    if (ac != 2) return 84;
    if (strcmp(argv[1], "-help") == 0) return print_help();
    if (error_handling(ac, argv) != 0) return 84;
    return start_server(atoi(argv[1]));
}
