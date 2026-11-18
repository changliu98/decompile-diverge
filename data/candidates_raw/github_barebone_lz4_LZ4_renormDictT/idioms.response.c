void LZ4_resetDict(struct LZ4_stream_t *LZ4_stream, int nextSize)
{
  int i;
  unsigned int delta;
  unsigned char *dictEnd;
  if (LZ4_stream->currentOffset + nextSize > 0x80000000)
  {
    delta = LZ4_stream->currentOffset - 0x10000;
    dictEnd = LZ4_stream->dictionary + LZ4_stream->dictSize;
    for (i = 0; i < 4096; i++)
    {
      if (LZ4_stream->hashTable[i] < delta)
        LZ4_stream->hashTable[i] = 0;
      else
        LZ4_stream->hashTable[i] -= delta;
    }
    LZ4_stream->currentOffset = 0x10000;
    if (LZ4_stream->dictSize > 0x10000)
      LZ4_stream->dictSize = 0x10000;
    LZ4_stream->dictionary = dictEnd - LZ4_stream->dictSize;
  }
}