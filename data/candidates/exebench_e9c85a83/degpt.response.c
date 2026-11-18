void triggers_bug(int *p)

{
  int *p_local;
  
  *p = -0x21524111;
  return;
}