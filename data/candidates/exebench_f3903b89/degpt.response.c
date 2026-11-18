void get_payload_info(char *bzimage_ptr, int *payload_offset, int *payload_size)
{
    // Calculate the payload offset by combining the sector count from 0x1f1 and the 32-bit offset from 0x248
    *payload_offset = (uint)(byte)(bzimage_ptr[0x1f1] + 1) * 0x200 + *(int *)(bzimage_ptr + 0x248);
    // Read the payload size from offset 0x24c
    *payload_size = *(int *)(bzimage_ptr + 0x24c);
}