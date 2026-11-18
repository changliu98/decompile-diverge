// Sends a specified number of bytes to the given port
// Parameters:
//   port - The port identifier to send data to
//   data - Pointer to the data buffer to be sent
//   len  - Number of bytes to send
// Returns:
//   0 on success
int sendbytes(int port_id, uchar *buffer, int byte_count)
{
    // Write the data to the specified port
    // Cast len to ulong via uint to match the expected parameter type of write()
    write(port_id, buffer, (ulong)(uint)byte_count);
    return 0;
}