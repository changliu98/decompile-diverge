// Creates a TCP socket and connects to the specified server IP and port.
// Returns 0 on success, -1 on failure.
int connectToServer(int *socket_fd, char *ip_address, int port)
{
    // Create a new socket (AF_INET, SOCK_STREAM, TCP)
    int socket_fd_local = socket(2, 1, 0);
    // Check if socket creation failed
    if (socket_fd_local == -1) {
        return -1;
    }
    // Store the socket file descriptor in the output parameter
    *socket_fd = socket_fd_local;
    // Initialize sockaddr_in structure for IPv4
    sockaddr_in server_address;
    // Set address family to IPv4 (AF_INET)
    server_address.sin_family = 2;
    // Convert server IP string to network byte order address
    server_address.sin_addr.s_addr = inet_addr(ip_address);
    // Convert server port to network byte order
    server_address.sin_port = htons((uint16_t)port);
    // Attempt to connect to the server
    // Note: sizeof(sockaddr_in) is typically 16 bytes (0x10)
    if (connect(socket_fd_local, (sockaddr *)&server_address, 0x10) == -1) {
        // Close the socket if connection fails
        close(socket_fd_local);
        return -1;
    }
    // Connection successful
    return 0;
}