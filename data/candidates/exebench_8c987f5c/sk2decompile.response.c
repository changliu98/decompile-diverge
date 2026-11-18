static const char *minimum_size_type(int min, int max, int *size) {
  const char *type = "int";
  int s = 4;
  if (min >= 0) {
    if (max < 256) {
      type = "unsigned char";
      s = 1;
    } else if (max < 65536) {
      type = "unsigned short int";
      s = 2;
    } else {
      type = "unsigned int";
      s = 4;
    }
  } else {
    if (min >= -127 && max < 128) {
      type = "signed char";
      s = 1;
    } else if (min >= -32767 && max < 32767) {
      type = "short";
      s = 2;
    }
  }
  if (size) {
    *size = s;
  }
  return type;
}