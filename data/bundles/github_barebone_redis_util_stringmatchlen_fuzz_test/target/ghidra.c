/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int stringmatchlen_fuzz_test(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int j_1;
  int j;
  int patlen;
  int strlen;
  int total_matches;
  int cycles;
  char pat [32];
  char str [32];
  
  cycles = 10000000;
  total_matches = 0;
  while (cycles != 0) {
    uVar1 = rand();
    uVar2 = rand();
    for (j = 0; j < (int)(uVar1 & 0x1f); j = j + 1) {
      iVar3 = rand();
      str[j] = (char)(iVar3 % 0x80);
    }
    for (j_1 = 0; j_1 < (int)(uVar2 & 0x1f); j_1 = j_1 + 1) {
      iVar3 = rand();
      pat[j_1] = (char)(iVar3 % 0x80);
    }
    iVar3 = stringmatchlen(pat,uVar2 & 0x1f,str,uVar1 & 0x1f,0);
    total_matches = iVar3 + total_matches;
    cycles = cycles + -1;
  }
  return total_matches;
}