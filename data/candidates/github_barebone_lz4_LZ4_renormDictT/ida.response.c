void __cdecl LZ4_renormDictT(LZ4_stream_t_internal *LZ4_dict, int nextSize)
{
  int i; // [rsp+0h] [rbp-1Ch]
  const BYTE *dictEnd; // [rsp+4h] [rbp-18h]
  U32 delta; // [rsp+Ch] [rbp-10h]

  if ( nextSize + LZ4_dict->currentOffset > 0x80000000 )
  {
    delta = LZ4_dict->currentOffset - 0x10000;
    dictEnd = &LZ4_dict->dictionary[LZ4_dict->dictSize];
    for ( i = 0; i < 4096; ++i )
    {
      if ( LZ4_dict->hashTable[i] >= delta )
        LZ4_dict->hashTable[i] -= delta;
      else
        LZ4_dict->hashTable[i] = 0;
    }
    LZ4_dict->currentOffset = 0x10000;
    if ( LZ4_dict->dictSize > 0x10000 )
      LZ4_dict->dictSize = 0x10000;
    LZ4_dict->dictionary = &dictEnd[-LZ4_dict->dictSize];
  }
}