#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "hacking.h"

#define PORT 80 // http port to clients connect to the server
#define WEBROOT "./webroot"

void imprimir_banner() {
    printf("TinyWeb Server\n");
    printf("Porta: %d\n", PORT);
    printf("Diretório raiz: %s\n", WEBROOT);
}
void handle_connection(int, struct sockaddr_in *);
long get_file_size(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return -1;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

int main(void) {
    imprimir_banner();

    int sockfd, newsockfd, yes = 1;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size;

    printf("Accepting web requests on port %d\n", PORT);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fatal("in socket");
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        fatal("in setsockopt");
    }

    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(PORT); // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any address and automatically fill with my ip
    memset(&(server_addr.sin_zero), '\0', 8); // Zero out the rest of the struct
    
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        fatal("in binding to socket");
    }

    if (listen(sockfd, 20) == -1) {
        fatal("in listening on socket");
    }

    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        if ((newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size)) == -1) {
            fatal("accepting connection"); // Continue to the next iteration if accept fails
        }

        handle_connection(newsockfd, &client_addr);
    }

    return 0;
}


/* This function handles the connection on the passed socket
 * from the client adsress. The connection is processed as a web request,
 * and this fucntion replies over the connected socket. Finally, the 
 * passed socket is closed at the end of the funtion
*/
void handle_connection(int sockfd, struct sockaddr_in *client_addr_ptr) {
    char request[1024];
    char response[4096];
    char *file_path;
    int file_size;

    printf("Connection from %s:%d\n", inet_ntoa(client_addr_ptr->sin_addr), ntohs(client_addr_ptr->sin_port));

    if (recv(sockfd, request, sizeof(request), 0) <= 0) {
        close(sockfd);
        return;
    }

    printf("Request: %s\n", request);

    if (strncmp(request, "GET ", 4) == 0) {
        file_path = request + 4;
        char *end = strchr(file_path, ' ');
        if (end) *end = '\0';
    } else {
        close(sockfd);
        return;
    }

    if (strcmp(file_path, "/") == 0)
        file_path = "/index.html";

    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s%s", WEBROOT, file_path);

    FILE *file = fopen(full_path, "rb");
    if (!file) {
        snprintf(response, sizeof(response), "HTTP/1.1 404 Not Found\r\n\r\n");
        send(sockfd, response, strlen(response), 0);
        close(sockfd);
        return;
    }

    file_size = get_file_size(full_path);

    snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\n"
            "Content-Length: %d\r\n"
            "Content-Type: text/html\r\n"
            "\r\n", file_size);

    send(sockfd, response, strlen(response), 0);

    while ((file_size = fread(response, 1, sizeof(response), file)) > 0) {
        send(sockfd, response, file_size, 0);
    }

    fclose(file);
    close(sockfd);
    printf("Response sent and connection closed.\n");

}
