int sendcw(int socket_fd, uchar *data_buffer)
{
    ssize_t bytes_sent;
    uint *error_code_ptr;

    // Send 18 bytes of data to the socket/file descriptor
    bytes_sent = send(socket_fd, data_buffer, 0x12, 0);
    if (bytes_sent == -1) {
        // Retrieve the last error code
        error_code_ptr = (uint *)__errno_location();
        // Log the error with priority 3 (LOG_ERR)
        syslog(3, "ca.so: Send cw failed %d", (ulong)*error_code_ptr);
    }
    // Return 1 if send was successful, 0 otherwise
    return (uint)(bytes_sent != -1);
}