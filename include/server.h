/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#ifndef SERVER_HPP
    #define SERVER_HPP

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/select.h>
    #include <errno.h>
    #include <signal.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <uuid/uuid.h>
    #include <ctype.h>
    #include <uuid/uuid.h>
    #include <dirent.h>
    #include "../libs/myteams/logging_server.h"
    #define MAX_CLIENTS 50
    #define BUFFER_SIZE 1024
    #define MAX_USERNAME_LENGTH 50
    #define MAX_PASSWORD_LENGTH 50
    #define MAX_PATH_LENGTH 200
    #define MAX_COMMAND_LENGTH 5
    #define MAX_ARGUMENT_LENGTH 50
    #define SEND_ERR "Error when sending a message to the client."
    #define ACTIVITY_ERR "Error while waiting for activity on a socket."
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

    typedef struct message {
        char *dest_name;
        char *dest_uuid;
        char *dest_path;
        char *cli_uuid;
        char *cli_path;
    } message_t;

    struct user {
        char **username;
        char **uuid;
        int nb_client;
    };

    typedef struct client {
        int socket;
        struct sockaddr_in address;
        int auth;
        char *command;
        char **argument;
        int nb_arg;
        char *name;
        char *uuid;
        bool actif;
        char *buff_temp;
        int id;
        struct user *user;
    } client_t;

    typedef struct server {
        int control_socket;
        int data_socket;
        struct sockaddr_in address;
        fd_set read_fds;
        int max_fd;
        int activity;
        int nbClients;
    } server_t;

    //cmd
    int check_cmd(server_t *server, client_t **client, int i);
    int login_command(client_t **client, int i);
    int logout_command(client_t *client, server_t *server, int i);
    int users_command(client_t **client, int i);
    int send_command(client_t **client, int i);
    int user_cmd(client_t **client, int ic);
    void print_user_info(client_t **client, int ic);

    // Tools
    server_t *print_error_server(char *message);
    int print_error_int(char *message);
    int print_help(void);
    int is_number_port(const char *str);
    int error_handling(int ac, char **argv);
    void parse_cmd(char *buffer, client_t *client, int i);
    int count_char(char *str, char c);
    int remove_quotes(client_t *client);
    char **get_directory_files(char *path);
    void set_info_client(client_t *client, char *user_name);
    char *generate_uuid(void);
    char *open_file(char *path);
    char *get_user(char *user_name);
    char *replace_char(char *s1, char *s2, char *s3);
    char *who_is_this_uuid(client_t *client);
    bool is_conversation_exist(client_t *client, char *path);
    int is_connecting_dest(client_t **client, char *dest_uuid);
    void free_message(message_t *mess);
    int count_array(char **array);

    // Init
    server_t *init_server(int port);
    client_t **init_client_struct(server_t *server);
    message_t *init_message(client_t *client);

    // Process
    int setup_socket(server_t *server, client_t **client);
    int check_new_client(server_t *server, client_t **client);
    int activity_client_socket(server_t *server, client_t **client);
    int client_command(server_t *server, client_t **client, int i);

#endif /* !SERVER_HPP */
