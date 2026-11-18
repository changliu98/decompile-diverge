static int vcolon(const unsigned char *data, long size, long offset) {
  if (offset == size) return -(offset + 1);
  if (data[offset] == ':') return offset + 1;
  while (data[offset] == ' ' || data[offset] == '\t' || data[offset] == '\r' ||
         data[offset] == '\n') {
    offset++;
    if (offset >= size) return -(offset + 1);
  }
  if (data[offset] == ':') return offset + 1;
  return -(offset + 1);
}