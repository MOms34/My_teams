/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "../../include/server.h"

int check_cmd3(server_t *server, client_t **client, int i)
{
    return -1;

}

int check_cmd2(server_t *server, client_t **client, int i)
{
    if (strcmp(client[i]->command, "/logout") == 0 && client[i]->nb_arg == 0) {
        logout_command(client[i], server, 1);
        return 0;
    }
    if (strcmp(client[i]->command, "/users") == 0 && client[i]->nb_arg == 0) {
        users_command(client, i);
        return 0;
    }
    if (strcmp(client[i]->command, "/send") == 0 && client[i]->nb_arg == 2) {
        send_command(client, i);
        return 0;
    }
    if (strcmp(client[i]->command, "/user") == 0 && client[i]->nb_arg == 1) {
        print_user_info(client, i);
        return 0;
    }
    return check_cmd3(server, client, i);
}

int check_cmd(server_t *server, client_t **client, int i)
{
    if (strcmp(client[i]->command, "/login") == 0 && client[i]->nb_arg == 1
    && client[i]->auth == 0) {
        if (strlen(client[i]->argument[0]) > MAX_NAME_LENGTH) return -1;
        login_command(client, i);
        return 0;
    }
    if (client[i]->auth == 1) return check_cmd2(server, client, i);
    return -1;
}
