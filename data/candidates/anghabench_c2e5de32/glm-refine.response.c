unsigned int __cdecl ff_rescale_rms(unsigned int rms, unsigned int energy)
{
  return (energy * rms) / 1024;
}