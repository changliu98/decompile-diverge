static int fons__decutf8(int* state, unsigned int* code, unsigned int ch) {
  int type = utf8d[ch];
  if (*state != UTF8_ACCEPT)
    *code = (*code << 6) | (ch & 0x3f);
  else
    *code = ch & (0xff >> type);
  *state = utf8d[256 + *state + type];
  return *state;
}