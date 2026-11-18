/**
 * @brief Writes data to a socket and returns the number of bytes not written.
 *
 * @param sockhandle The socket file descriptor.
 * @param buf        Pointer to the buffer containing data to write.
 * @param length     The number of bytes to attempt to write.
 * @return           The number of bytes that were not written (0 if all bytes were written successfully).
 */
int write_sock(int socket_fd, uchar *data_buffer, int buffer_size)
{
    // Return the difference between the requested length and the actual bytes written.
    // If write() returns -1 on error, this will result in length + 1, indicating an error.
    return buffer_size - write(socket_fd, data_buffer, buffer_size);
}