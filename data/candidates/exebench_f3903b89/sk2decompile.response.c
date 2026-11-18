void get_payload_info(unsigned char *buf, unsigned int *payload_offset,
                      unsigned int *payload_size) {
  unsigned int payload_size_high;
  payload_size_high = buf[0x1e1] + 1;
  *payload_offset = buf[0x9a] + (payload_size_high << 9);
  *payload_size = *(unsigned int *)(buf + 0x9b);
}