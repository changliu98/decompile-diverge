// Creates a pair of connected Unix domain sockets.
// Parameters:
//   d       - Domain (e.g., AF_UNIX)
//   type    - Socket type (e.g., SOCK_STREAM or SOCK_DGRAM)
//   protocol - Protocol to use (usually 0 for default)
//   sv      - Array of two integers to store the socket file descriptors
// Returns:
//   0 on success, -1 on error
int unix_socketpair(int domain, int socket_type, int protocol, int *sv)
{
    // Call the underlying socketpair system call
    return socketpair(d, type, protocol, sv);
}