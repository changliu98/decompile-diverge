void cgi_network_get_action(char *shared_memory_buffer)
{
    // Set byte at offset 4 to action type 0x02 (GET)
    shared_memory_buffer[4] = '\x02';
    // Set byte at offset 5 to 0 (reserved/unused)
    shared_memory_buffer[5] = '\0';
    // Set byte at offset 6 to 0 (reserved/unused)
    shared_memory_buffer[6] = '\0';
    // Set byte at offset 7 to 0 (reserved/unused)
    shared_memory_buffer[7] = '\0';
    // Set byte at offset 8 to 0x01 (version or flag)
    shared_memory_buffer[8] = '\x01';
    // Set byte at offset 9 to 0 (reserved/unused)
    shared_memory_buffer[9] = '\0';
    // Set byte at offset 10 to 0 (reserved/unused)
    shared_memory_buffer[10] = '\0';
    // Set byte at offset 11 (0xb) to 0 (reserved/unused)
    shared_memory_buffer[0xb] = '\0';
}