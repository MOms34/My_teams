/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/server.h"

void write_message_on_file(char *line, FILE *fichier, FILE *fichier_tmp,
char *message_f)
{
    while (fgets(line, sizeof(line), fichier) != NULL) {
        if (strstr(line, "---") != NULL) {
            fputs(message_f, fichier_tmp);
            fputs("\n---\n", fichier_tmp);
            break;
        }
        fputs(line, fichier_tmp);
    }
}

void add_message(char *uuid_f, char *message, char *path, char *name_cli)
{
    char *path_tmp = replace_char(path, "txt", "tmp");
    int size = strlen(message) + strlen(name_cli) + 3;
    char *message_f = malloc(sizeof(char) * (size + 1));
    FILE *fichier = fopen(path, "r");
    FILE *fichier_tmp = fopen(path_tmp, "w");
    char line[BUFFER_SIZE];

    snprintf(message_f, size, "%s: %s", name_cli, message);
    message_f[size] = '\0';
    while (fgets(line, sizeof(line), fichier) != NULL) {
        if (strstr(line, uuid_f) != NULL) {
            fputs(line, fichier_tmp);
            write_message_on_file(line, fichier, fichier_tmp, message_f);
        } else
            fputs(line, fichier_tmp);
    }
    fclose(fichier);
    fclose(fichier_tmp);
    remove(path);
    rename(path_tmp, path);
}

void create_conversation(char *cli_uuid, char *dest_path)
{
    FILE *fp = fopen(dest_path, "a");

    if (fp == NULL) return;
    fprintf(fp, "\n%s\n---\n", cli_uuid);
    fclose(fp);
}

void send_and_response(client_t **client, int i)
{
    int i_dest = is_connecting_dest(client, client[i]->argument[0]);
    char *resp = NULL;
    int size = 0;

    if (i_dest != -1) {
        server_event_private_message_sended(client[i]->uuid,
        client[i]->argument[0], client[i]->argument[1]);
        size = strlen(client[i]->uuid) + strlen(client[i]->argument[1]) + 4;
        resp = malloc(sizeof(char) * (size + 1));
        snprintf(resp, size, "c-%s|%s|", client[i]->uuid,
        client[i]->argument[1]);
        write(client[i_dest]->socket, resp, size);
    } else {
        size = strlen(client[i]->argument[0]) + 9;
        resp = malloc(sizeof(char) * (size + 1));
        snprintf(resp, size, "c-error|%s|", client[i]->argument[0]);
        write(client[i]->socket, resp, size);
    }
}

int send_command(client_t **client, int i)
{
    message_t *mess = init_message(client[i]);

    if (mess != NULL) {
        if (is_conversation_exist(client[i], mess->dest_path) == true) {
            add_message(mess->cli_uuid, client[i]->argument[1],
            mess->dest_path, client[i]->name);
            add_message(mess->dest_uuid, client[i]->argument[1],
            mess->cli_path, client[i]->name);
        } else {
            create_conversation(mess->cli_uuid, mess->dest_path);
            create_conversation(mess->dest_uuid, mess->cli_path);
            add_message(mess->cli_uuid, client[i]->argument[1],
            mess->dest_path, client[i]->name);
            add_message(mess->dest_uuid, client[i]->argument[1],
            mess->cli_path, client[i]->name);
        }
        send_and_response(client, i);
    }
    free_message(mess);
    return 0;
}
