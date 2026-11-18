int aligned(int val)

{
  int val_local;
  
  return (val + 0x3f >> 6) << 6;
}