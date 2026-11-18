void __cdecl arcfour_generate_stream(BYTE *state, BYTE *out, size_t len)
{
  BYTE t; // [rsp+Fh] [rbp-29h]
  size_t idx; // [rsp+10h] [rbp-28h]
  int j; // [rsp+18h] [rbp-20h]
  int i; // [rsp+1Ch] [rbp-1Ch]

  idx = 0LL;
  i = 0;
  j = 0;
  while ( idx < len )
  {
    i = (i + 1) % 256;
    j = (state[i] + j) % 256;
    t = state[i];
    state[i] = state[j];
    state[j] = t;
    out[idx++] = state[(state[j] + state[i]) % 256];
  }
}