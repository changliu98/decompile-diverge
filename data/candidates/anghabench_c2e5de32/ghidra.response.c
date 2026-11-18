uint ff_rescale_rms(uint rms,uint energy)

{
  uint energy_local;
  uint rms_local;
  
  return rms * energy >> 10;
}