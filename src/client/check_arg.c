/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "../../include/client.h"

int is_number_port(const char *str)
{
    int i = 0;
    int port;

    while (str[i] != '\0') {
        if (!isdigit(str[i]))
            return -1;
        i++;
    }
    port = atoi(str);
    if (port < 1 || port > 65535) {
        printf("Invalid port.\n");
        return -1;
    }
    return 0;
}
