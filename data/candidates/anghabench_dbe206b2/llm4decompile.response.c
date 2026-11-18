int get_opcode(unsigned char *buf, uint32_t *opcode)
{
    if (buf[0] == 0x0f) {
        *opcode = *(uint16_t *)buf;
        return 2;
    } else {
        *opcode = buf[0];
        return 1;
    }
}