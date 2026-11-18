void zywrleCalcSize(int *pW,int *pH,int level)

{
  int level_local;
  int *pH_local;
  int *pW_local;
  
  *pW = ((1 << ((byte)level & 0x1f)) - 1U ^ 0xffffffff) & *pW;
  *pH = ((1 << ((byte)level & 0x1f)) - 1U ^ 0xffffffff) & *pH;
  return;
}