uint dac_lsb_4020_reg(uint channel)

{
  uint channel_local;
  
  return (channel & 1) * 4 + 0x70;
}