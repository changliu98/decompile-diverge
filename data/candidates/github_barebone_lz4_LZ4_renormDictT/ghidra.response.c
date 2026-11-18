void LZ4_renormDictT(LZ4_stream_t_internal *LZ4_dict,int nextSize)

{
  uint uVar1;
  LZ4_byte *pLVar2;
  uint uVar3;
  int i;
  BYTE *dictEnd;
  U32 delta;
  int nextSize_local;
  LZ4_stream_t_internal *LZ4_dict_local;
  
  if (0x80000000 < LZ4_dict->currentOffset + nextSize) {
    uVar3 = LZ4_dict->currentOffset - 0x10000;
    pLVar2 = LZ4_dict->dictionary;
    uVar1 = LZ4_dict->dictSize;
    for (i = 0; i < 0x1000; i = i + 1) {
      if (LZ4_dict->hashTable[i] < uVar3) {
        LZ4_dict->hashTable[i] = 0;
      }
      else {
        LZ4_dict->hashTable[i] = LZ4_dict->hashTable[i] - uVar3;
      }
    }
    LZ4_dict->currentOffset = 0x10000;
    if (0x10000 < LZ4_dict->dictSize) {
      LZ4_dict->dictSize = 0x10000;
    }
    LZ4_dict->dictionary = pLVar2 + ((ulong)uVar1 - (ulong)LZ4_dict->dictSize);
  }
  return;
}