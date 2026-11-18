/* WARNING: Removing unreachable block (ram,0x001011e3) */

void cpuid_detect(int *sse2,int *sse3)

{
  long lVar1;
  uint uVar2;
  int d;
  int c;
  int b;
  int a;
  int *sse3_local;
  int *sse2_local;
  
  lVar1 = cpuid_Version_info(1);
  uVar2 = *(uint *)(lVar1 + 0xc);
  if (sse2 != (int *)0x0) {
    *sse2 = *(int *)(lVar1 + 8) >> 0x1a & 1;
  }
  if (sse3 != (int *)0x0) {
    *sse3 = uVar2 & 1;
  }
  return;
}