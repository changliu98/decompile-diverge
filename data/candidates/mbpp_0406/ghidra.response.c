char * func0(uint x)

{
  uint uVar1;
  uint y;
  uint x_local;
  char *local_10;
  
  uVar1 = x ^ x >> 1;
  uVar1 = uVar1 ^ uVar1 >> 2;
  uVar1 = uVar1 ^ uVar1 >> 4;
  uVar1 = uVar1 ^ uVar1 >> 8;
  if (((uVar1 ^ uVar1 >> 0x10) & 1) == 0) {
    local_10 = "Even Parity";
  }
  else {
    local_10 = "Odd Parity";
  }
  return local_10;
}