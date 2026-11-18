void toggle(int *v)

{
  int *v_local;
  
  *v = (uint)((*v != 0 ^ 0xffU) & 1);
  return;
}