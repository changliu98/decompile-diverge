void dopr_outch(char *buf, unsigned int *buf_pos, unsigned int buf_size,
                char c) {
  if (*buf_pos < buf_size) {
    buf[*buf_pos] = c;
  }
  (*buf_pos)++;
}