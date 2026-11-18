uint myrnd(uint *seed_ptr,int n)

{
  uint uVar1;
  uint val;
  uint seed;
  int n_local;
  uint *seed_ptr_local;
  
  uVar1 = *seed_ptr * 0x4cb2f + 1;
  if (n == 0x100) {
    val = uVar1 >> 0x18;
  }
  else {
    val = uVar1 % (uint)n;
  }
  *seed_ptr = uVar1;
  return val;
}