float add_denormal_prevention_white_noise(uint *rand_state)

{
  int flt_rnd;
  int mantissa;
  uint *rand_state_local;
  
  *rand_state = *rand_state * 0x12d687 + 0xd950b;
  return (float)(*rand_state & 0x7f0000 | 0x1e000000);
}