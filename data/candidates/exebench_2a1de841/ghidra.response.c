double linsched_rand(uint *state)

{
  uint uVar1;
  uint rand;
  uint *state_local;
  
  uVar1 = (*state * 0x41a7) % 0x7fffffff;
  *state = uVar1;
  return (double)uVar1 / DAT_00102008;
}