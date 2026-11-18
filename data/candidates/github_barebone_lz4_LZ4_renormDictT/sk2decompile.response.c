static void LZ4_renormDictT(LZ4_Data_Structure* d4, int nbBytes) {
  if (d4->currentOffset + nbBytes > 0x80000000) {
    U32 minValue = d4->currentOffset - 64 * 1024;
    const BYTE* p = d4->dictionary + d4->dictSize;
    int i;
    for (i = 0; i < 4096; i++) {
      if (d4->base[i] < minValue)
        d4->base[i] = 0;
      else
        d4->base[i] -= minValue;
    }
    d4->currentOffset = 64 * 1024;
    if (d4->dictSize > 64 * 1024) d4->dictSize = 64 * 1024;
    d4->dictionary = p - d4->dictSize;
  }
}