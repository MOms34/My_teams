/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** client_process.c
*/

#include "../../include/client.h"

char *get_input(client_t *client, fd_set fds)
{
    char *str = NULL;
    size_t len = 0;

    if (FD_ISSET(STDIN_FILENO, &fds)) {
        FD_ZERO(&client->input_fds);
        FD_SET(STDIN_FILENO, &client->input_fds);
        getline(&str, &len, stdin);
    }
    return str;
}

int treatment_input(client_t *client, char *input)
{
    if (input == NULL) return 0;
    if (strncmp(input, "/exit", 5) == 0) return 1;
    if (strncmp(input, "/help", 5) == 0) return help_command();
    if (strncmp(input, "/login", 6) == 0) return login_command(client, input);
    if (strncmp(input, "/logout", 7) == 0 && client->auth == 1)
        return logout_command(client, input);
    if (strncmp(input, "/users", 6) == 0) return users_command(client, input);
    if (strncmp(input, "/user", 5) == 0) return users_command(client, input);
    if (strncmp(input, "/send", 5) == 0) return send_command(client, input);
    return 0;
}
