/**
 * @brief Writes data to a serial port.
 *
 * @param portId The file descriptor of the serial port.
 * @param data Pointer to the data buffer to be written.
 * @param length The number of bytes to write.
 * @return The number of bytes written on success, or -1 on error.
 */
int Serial_WriteData(int fd, uchar *buffer, int num_bytes)
{
    // Write 'length' bytes from 'data' to the serial port identified by 'portId'
    return write(fd, buffer, num_bytes);
}