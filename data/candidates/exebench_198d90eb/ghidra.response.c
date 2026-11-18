void advance_kpos(int *kpos)

{
  int *kpos_local;
  
  *kpos = (*kpos + 1) % 0x29;
  kpos[1] = (kpos[1] + 1) % 0x1f;
  kpos[2] = (kpos[2] + 1) % 0x1d;
  kpos[3] = (kpos[3] + 1) % 0x1a;
  kpos[4] = (kpos[4] + 1) % 0x17;
  return;
}