#ifndef _COMM
#define _COMM "COMM"
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__) || defined(__APPLE__)
#if defined(__linux__) && defined(kernel_version_2_4)
#include <sys/sendfile.h>
#endif
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#elif _WIN32
#include <winsock2.h>
typedef short ssize_t;
typedef int socklen_t;
#define xs_SOCKET SOCKET
#define xs_ERROR INVALID_SOCKET
#else
#error OS not supported
#endif

#include <crosssocket.h>

#define COMM_BUFFER_SIZE 256
#define COMM_SERV_BACKLOG 10

/*
 * Loads operating system specific libraries
 */
int comm_init();

/*
 * Frees up memory
 */
int comm_clean();

/*
 * Check if the given port is valid
 * @param port The port number to be checked
 * @return 0 is return for success and -1 indicates failure
 */
int comm_check_port(int port);

/*
 * Write binary data to a given socket
 * @param sockfd The socket descriptor to write to
 * @param buffer The binary to be written to the socket
 * @return Success value is returned mentioning a value is sent or not
 * 0 for success
 * 1 for failure
 */
int comm_write_binary(xs_SOCKET sockfd, const void *buffer);

/*
 * Write data to a given socket
 * @param sockfd The socket descriptor to write to
 * @param buffer The message to be written to the socket
 * @return Success value is returned mentioning a value is sent or not
 * 0 for success
 * 1 for failure
 */
int comm_write_text(xs_SOCKET sockfd, const char *buffer);

/*
 * Read text data from a socket, reads a write or until max_len is
 * achieved. Strips the ending characters: \r, \n, \r\n.
 * The returned text might be less than max_len
 * @param sockfd The socket descriptor to write to
 * @return buffer data from the socket. NULL indicates
 * connection has been closed or error has been occured
 */
char *comm_read_text(xs_SOCKET sockfd, int max_len);

/*
 * Read binary data from a socket, read until socket is closed,
 * if the given buffer points to null the memory will be
 * allocated with respect to bufflen
 * @param sockfd The socket descriptor to write to
 * @param buffer The buffer to store the data
 * @param The length of the buffer
 * @return buffer data from the socket
 */
int comm_read_binary(xs_SOCKET sockfd, char *buffer, int bufflen);

/*
 * closes the socket if it open
 * @param sockfd The socket to be closed
 */
int comm_close_socket(xs_SOCKET sockfd);

/** Connects to the server with the standard IPv4 and TCP stack
 * @param hostname IPv4 address or hostname
 * @param port Port number for the server to start
 * @return Socket descriptor of the started server
 */
xs_SOCKET comm_connect_server(const char *hostname, int port);

//TODO support multiple server options
/** Starts the server with the standard IPv4 and TCP stack
 * @param port Port number for the server to start
 * @return Socket descriptor of the started server
 */
xs_SOCKET comm_start_server(int port);

#ifdef __cplusplus
}
#endif
#endif
