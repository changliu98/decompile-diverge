void advance_m1pos(int *m1pos)

{
  int *m1pos_local;
  
  *m1pos = (*m1pos + 1) % 0x3d;
  return;
}