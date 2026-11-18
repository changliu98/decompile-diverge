int __cdecl sendbytes(int fd, unsigned __int8 *data, int len)
{
    // Cast len to size_t to match the standard POSIX signature of write()
    // The original decompiler output cast to unsigned int, which is functionally 
    // equivalent on most 32/64-bit platforms but size_t is more semantically correct.
    write(fd, data, (size_t)len);
    
    return 0;
}