int inet_close(int *socket_fd)
{
    // Close the socket file descriptor
    close(*socket_fd);
    // Set the socket pointer to 0 to indicate it is closed
    *socket_fd = 0;
    // Return success
    return 0;
}