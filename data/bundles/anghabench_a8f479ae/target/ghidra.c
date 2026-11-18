uint ice_txd_use_count(uint size)

{
  uint size_local;
  
  return (size * 0x55 >> 0x14) + 1;
}