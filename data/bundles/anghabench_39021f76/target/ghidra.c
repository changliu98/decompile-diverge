int all_bits_clear(uint test,uint mask)

{
  uint mask_local;
  uint test_local;
  
  return (int)((test & mask) == 0);
}