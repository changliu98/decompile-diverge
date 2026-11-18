static void get_payload_info(char *bzimage, int *offset, int *size)
{
 unsigned int system_offset;
 unsigned char setup_sectors;

 setup_sectors = bzimage[0x1f1] + 1;
 system_offset = setup_sectors * 512;
 *offset = system_offset + *((int*)&bzimage[0x248]);
 *size = *((int*)&bzimage[0x24c]);
}