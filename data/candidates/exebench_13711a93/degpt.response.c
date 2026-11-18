void cgi_sys_get_action(char *shared_memory_buffer)
{
    // Set byte at offset 4 to 0x06 (likely action type or command code)
    shared_memory_buffer[4] = '\x06';
    // Set bytes at offsets 5, 6, 7 to 0x00 (padding or reserved fields)
    shared_memory_buffer[5] = '\0';
    shared_memory_buffer[6] = '\0';
    shared_memory_buffer[7] = '\0';
    // Set byte at offset 8 to 0x01 (likely a flag or sub-action identifier)
    shared_memory_buffer[8] = '\x01';
    // Set bytes at offsets 9, 10, 11 to 0x00 (padding or reserved fields)
    shared_memory_buffer[9] = '\0';
    shared_memory_buffer[10] = '\0';
    shared_memory_buffer[0xb] = '\0';
}