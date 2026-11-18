void __cdecl arx_bwd(uint8_t *state)
{
  uint8_t s0 = state[0];
  uint8_t s1 = state[1];
  uint8_t s2 = state[2];
  uint8_t s3 = state[3];

  // Round 1
  s2 = ROR8(s2, 4);
  s1 ^= s2;
  s3 ^= s0;
  s1 = ROR8(s1, 3);
  s3 = ROR8(s3, 7);
  s0 -= s3;
  s2 -= s1;

  // Round 2
  s0 = ROR8(s0, 4);
  s1 ^= s0;
  s3 ^= s2;
  s1 = ROR8(s1, 2);
  s3 = ROR8(s3, 5);
  s0 -= s1;
  s2 -= s3;

  // Write back
  state[0] = s0;
  state[1] = s1;
  state[2] = s2;
  state[3] = s3;
}