void get_payload_info(char *buffer, unsigned int *k_offset, unsigned int *k_size)
{
 char setup_sectors;
 unsigned int system_offset;

 setup_sectors = buffer[497] + 1;
 system_offset = setup_sectors * 512;

 *k_offset = *(unsigned int *)(buffer + 584) + system_offset;
 *k_size = *(unsigned int *)(buffer + 588);
}