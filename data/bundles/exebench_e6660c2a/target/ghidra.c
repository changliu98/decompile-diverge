void foo(int *x,int y,int z)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int e;
  int d;
  int c;
  int b;
  int z_local;
  int y_local;
  int *x_local;
  
  iVar1 = *x;
  iVar2 = x[1];
  for (b = 0; b < 1; b = b + 1) {
    uVar4 = 0;
    if (iVar2 != 0) {
      uVar4 = 2;
    }
    uVar3 = 0;
    if (iVar1 != 0) {
      uVar3 = 2;
    }
    x[b + 2] = uVar3 | 1 >> ((byte)b & 0x1f) != 0 | y != 0 | uVar4 | (uint)(z != 0);
  }
  return;
}