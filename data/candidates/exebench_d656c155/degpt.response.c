int convertToBills(int dollars,int *hds,int *fts,int *tts,int *tns)

{
  ulong uVar1;
  int *tns_local;
  int *tts_local;
  int *fts_local;
  int *hds_local;
  int dollars_local;
  
  *hds = dollars / 100;
  *fts = (int)((long)((ulong)(uint)((int)((long)dollars % 100) >> 0x1f) << 0x20 |
                     (long)dollars % 100 & 0xffffffffU) / 0x32);
  uVar1 = (long)((ulong)(uint)((int)((long)dollars % 100) >> 0x1f) << 0x20 |
                (long)dollars % 100 & 0xffffffffU) % 0x32;
  *tts = (int)((long)((ulong)(uint)((int)uVar1 >> 0x1f) << 0x20 | uVar1 & 0xffffffff) / 0x14);
  uVar1 = (long)((ulong)(uint)((int)((long)dollars % 100) >> 0x1f) << 0x20 |
                (long)dollars % 100 & 0xffffffffU) % 0x32;
  uVar1 = (long)((ulong)(uint)((int)uVar1 >> 0x1f) << 0x20 | uVar1 & 0xffffffff) % 0x14;
  *tns = (int)((long)((ulong)(uint)((int)uVar1 >> 0x1f) << 0x20 | uVar1 & 0xffffffff) / 10);
  return dollars % 10;
}