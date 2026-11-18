int sdram_convert(uint pllin,uint *sdram_freq)

{
  uint tmp;
  uint ns;
  uint *sdram_freq_local;
  uint pllin_local;
  
  tmp = ((uint)(0x3d09 / (1000000000 / (ulong)pllin)) >> 6) + 1;
  if (0xff < tmp) {
    tmp = 0xff;
  }
  *sdram_freq = tmp;
  return 0;
}