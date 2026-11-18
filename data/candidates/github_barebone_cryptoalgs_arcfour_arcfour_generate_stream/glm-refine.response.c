void __cdecl arcfour_generate_stream(BYTE *state, BYTE *out, size_t len)
{
  int i = 0;
  int j = 0;

  for (size_t idx = 0; idx < len; idx++)
  {
    // Update indices
    i = (i + 1) % 256;
    j = (state[i] + j) % 256;

    // Swap state[i] and state[j]
    BYTE temp = state[i];
    state[i] = state[j];
    state[j] = temp;

    // Generate the next byte of the keystream
    out[idx] = state[(state[i] + state[j]) % 256];
  }
}