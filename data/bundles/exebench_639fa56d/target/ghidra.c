void advance_m2pos(int *m2pos)

{
  int *m2pos_local;
  
  *m2pos = (*m2pos + 1) % 0x25;
  return;
}