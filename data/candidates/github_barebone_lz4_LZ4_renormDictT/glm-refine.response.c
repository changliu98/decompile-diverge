define LZ4_NORMALIZE_BASE 0x10000

void __cdecl LZ4_renormDictT(LZ4_stream_t_internal *LZ4_dict, int nextSize)
{
  // Check if the current offset + next size will exceed the 2GB limit
  if ((U32)nextSize + LZ4_dict->currentOffset > LZ4_MAX_OFFSET)
  {
    U32 delta = LZ4_dict->currentOffset - LZ4_NORMALIZE_BASE;
    const BYTE *dictEnd = LZ4_dict->dictionary + LZ4_dict->dictSize;
    int i;

    // Normalize hash table entries by subtracting the delta
    for (i = 0; i < LZ4_HASH_SIZE; ++i)
    {
      if (LZ4_dict->hashTable[i] >= delta)
        LZ4_dict->hashTable[i] -= delta;
      else
        LZ4_dict->hashTable[i] = 0;
    }

    // Reset the current offset and cap the dictionary size
    LZ4_dict->currentOffset = LZ4_NORMALIZE_BASE;
    if (LZ4_dict->dictSize > LZ4_NORMALIZE_BASE)
      LZ4_dict->dictSize = LZ4_NORMALIZE_BASE;

    // Update the dictionary pointer to the new end boundary
    LZ4_dict->dictionary = dictEnd - LZ4_dict->dictSize;
  }
}