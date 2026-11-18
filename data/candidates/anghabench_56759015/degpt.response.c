uint dac_convert_reg(uint channel)

{
  uint channel_local;
  
  return (channel & 1) * 2 + 0x70;
}