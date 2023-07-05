/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "../../include/server.h"

void do_quote(client_t *client)
{
    char temp[256] = "\"";
    char temp2[2] = "\"\0";
    char temp3[256] = "\"";

    for (int j = 0; j < client->nb_arg; j++) {
        strcat(temp, client->argument[j]);
        strcat(temp, temp2);
        client->argument[j] = NULL;
        client->argument[j] = malloc(sizeof(char) * 256);
        strcpy(client->argument[j], temp);
        strcpy(temp, temp3);
    }
}

void check_last(char *buffer, client_t *client, int i, int arg_len)
{
    char *tokens[MAX_COMMAND_LENGTH];
    char *token = strtok(buffer, "\"");

    while (token != NULL && i < MAX_COMMAND_LENGTH) {
        if (i % 2 != 0)
            tokens[i] = strdup(token);
        token = strtok(NULL, "\"");
        i++;
    }
    client->nb_arg = i / 2;
    if (client->nb_arg > 0) {
        client->argument = malloc(sizeof(char*) * client->nb_arg);
        for (int j = 0; j < client->nb_arg; j++) {
            arg_len = strlen(tokens[j * 2 + 1]);
            client->argument[j] = malloc(sizeof(char) * (arg_len + 1));
            strncpy(client->argument[j], tokens[j * 2 + 1], arg_len + 1);
            client->argument[j][arg_len] = '\0';
        }
    }
    return do_quote(client);
}

void parse_cmd(char *buffer, client_t *client, int i)
{
    char *tokens[MAX_COMMAND_LENGTH];
    char *token = strtok(buffer, " ");

    while (token != NULL && i < MAX_COMMAND_LENGTH) {
        tokens[i] = strdup(token);
        token = strtok(NULL, " ");
        i++;
    }
    client->command = strdup(tokens[0]);
    if (strcmp(client->command, "/send") == 0)
        return check_last(client->buff_temp, client, 0, 0);
    if (i > 1) {
        client->argument = malloc(sizeof(char*) * (i - 1));
        for (int j = 0; j < (i - 1); j++) {
            client->argument[j] = strdup(tokens[j + 1]);
            client->argument[j][strlen(client->argument[j])] = '\0';
        }
        client->nb_arg = i - 1;
    } else
        client->argument = NULL;
}

int count_char(char *str, char c)
{
    int count = 0;

    for (int i = 0; i < strlen(str); i++)
        if (str[i] == c)
            count++;
    return count;
}

int remove_quotes(client_t *client)
{
    char *arg = NULL;
    int len = 0;

    if (client->nb_arg == 0) return 0;
    for (int i = 0; i < client->nb_arg; i++) {
        arg = client->argument[i];
        len = strlen(arg);
        if (len == 0) return -1;
        if (arg[0] != '"' || arg[len - 1] != '"'
        || count_char(arg, '"') != 2)
            return -1;
        memmove(arg, arg + 1, len - 2);
        arg[len - 2] = '\0';
    }
    if (strlen(arg) == 0)
        return -1;
    return 0;
}
