int file_packet_EOF_ACK(unsigned char *buf, int len) {
  int ret;
  unsigned char cmd;
  cmd = buf[0];
  if (cmd != 0x06) {
    return -1;
  }
  ret = buf[1];
  return ret;
}