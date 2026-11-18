void arcfour_generate_stream(unsigned char *state, unsigned char *stream,
                             unsigned long stream_length) {
  unsigned long i = 0;
  int x = 0;
  int y = 0;
  unsigned char temp;
  while (i < stream_length) {
    x = (x + 1) % 256;
    y = (y + state[x]) % 256;
    temp = state[x];
    state[x] = state[y];
    state[y] = temp;
    stream[i] = state[(state[x] + state[y]) % 256];
    i++;
  }
}