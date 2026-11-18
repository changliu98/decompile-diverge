void arcfour_generate_stream(unsigned char *state, unsigned char *out, unsigned long len)
{
  unsigned long i = 0;
  int a = 0; int b = 0;
  unsigned char tmp;
  for (i = 0; i < len; i++) {
    a = (a + 1) % 256;
    b = (state[a] + b) % 256;
    tmp = state[a];
    state[a] = state[b];
    state[b] = tmp;
    out[i] = state[(state[a] + state[b]) % 256];
  }
}