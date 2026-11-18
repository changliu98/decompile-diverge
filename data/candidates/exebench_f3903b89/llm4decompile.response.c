void get_payload_info(char *bzimage, int *offset, int *size)
{
    *offset = *(int *)(bzimage + 0x248) +
        ((*(unsigned char *)(bzimage + 0x1f1) + 1) << 9);
    *size = *(int *)(bzimage + 0x24c);
}