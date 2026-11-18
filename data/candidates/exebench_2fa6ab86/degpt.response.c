/**
 * @brief Receives data from a serial communication port.
 *
 * @param fComPort The file descriptor representing the communication port.
 * @param pData    Pointer to the buffer where received data will be stored.
 * @param nMaxLen  Maximum number of bytes to read.
 * @return         The number of bytes actually read, cast to short.
 *                 Returns -1 on error.
 */
short recv_data(int fd, uchar *buffer, unsigned_short max_len) {
    // Read up to nMaxLen bytes from the port into pData
    return (short)read(fd, buffer, (ulong)max_len);
}