void advance_spos(int *spos)

{
  int *spos_local;
  
  *spos = (*spos + 1) % 0x2b;
  spos[1] = (spos[1] + 1) % 0x2f;
  spos[2] = (spos[2] + 1) % 0x33;
  spos[3] = (spos[3] + 1) % 0x35;
  spos[4] = (spos[4] + 1) % 0x3b;
  return;
}