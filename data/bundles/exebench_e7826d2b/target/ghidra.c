void foo(int *p)

{
  int i;
  int *p_local;
  
  for (i = 0; i < 0x18; i = i + 1) {
    p[i] = p[i] + 1;
  }
  return;
}