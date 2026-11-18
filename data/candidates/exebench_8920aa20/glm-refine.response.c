int __cdecl medusaReceiveInternal(SOCKET socket, unsigned __int8 *buf, int length)
{
    // Wrapper around the standard `recv` function.
    // Returns the number of bytes received, or SOCKET_ERROR (-1) on failure.
    return recv(socket, (char *)buf, length, 0);
}