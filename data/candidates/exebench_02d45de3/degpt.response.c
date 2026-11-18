/**
 * Writes data to a bus device.
 *
 * @param busfd   File descriptor of the bus device.
 * @param buf     Pointer to the buffer containing data to write.
 * @param bufsize Number of bytes to write from the buffer.
 * @return        Number of bytes written on success, or -1 on error.
 */
int write_bus(int bus_fd, uchar *data_buffer, int buffer_size)
{
    return write(bus_fd, data_buffer, buffer_size);
}