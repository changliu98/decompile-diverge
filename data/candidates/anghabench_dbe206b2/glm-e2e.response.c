int get_opcode(unsigned char *ptr, unsigned int *opcode) {
    if (*ptr == 0xf) {
        *opcode = *(unsigned short *)ptr;
        return 2;
    } else {
        *opcode = *ptr;
        return 1;
    }
}