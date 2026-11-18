int get_opcode(unsigned char *buf, unsigned int *opcode) {
  if (buf[0] == 0x0f) {
    *opcode = buf[0] << 8 | buf[1];
    return 2;
  } else {
    *opcode = buf[0];
    return 1;
  }
}