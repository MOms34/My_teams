/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#ifndef CLIENT_HPP
    #define CLIENT_HPP

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/select.h>
    #include <sys/stat.h>
    #include <errno.h>
    #include <signal.h>
    #include <sys/wait.h>
    #include <ctype.h>
    #include <poll.h>
    #include <uuid/uuid.h>
    #include "../libs/myteams/logging_client.h"
    #define MAX_CLIENTS 50
    #define BUFFER_SIZE 1024
    #define MAX_USERNAME_LENGTH 50
    #define MAX_PASSWORD_LENGTH 50
    #define MAX_PATH_LENGTH 200
    #define MAX_COMMAND_LENGTH 5
    #define MAX_ARGUMENT_LENGTH 50
    #define SEND_ERR "Error when sending a message to the server."
    #define READ_ERR "Error when reading a message from the server."
    #define ACTIVITY_ERR "Error while waiting for activity on a socket."

    typedef struct client {
        int socket;
        struct sockaddr_in address;
        int auth;
        char *ip;
        int port;
        fd_set read_fds;
        int max_fd;
        int activity;
        fd_set input_fds;
        char *user_name;
        char *user_id;
    } client_t;

    // Tools
    int is_number_port(const char *str);
    int print_help_client(void);
    int print_error_int(char *message);
    int error_handling(int ac, char **argv);
    void clean_client(client_t *client);
    char *open_file(char *path);

    // Init
    client_t *init_client(char *ip, int port);

    // Process
    fd_set listen_activity(client_t *client, int *maxfd,
    struct timeval *timeout);
    int activity_server_socket(client_t *client, fd_set fds);
    char *get_input(client_t *client, fd_set fds);
    int treatment_input(client_t *client, char *input);

    // Commands
    int help_command(void);
    int login_command(client_t *client, char *input);
    void login_resp(client_t *client, char *resp);
    int logout_command(client_t *client, char *input);
    int users_command(client_t *client, char *input);
    void users_resp(client_t *client, char *resp);
    int send_command(client_t *client, char *input);
    void send_resp(client_t *client, char *resp);
    void user_resp(client_t *client, char *resp);

#endif /* !CLIENT_HPP */
