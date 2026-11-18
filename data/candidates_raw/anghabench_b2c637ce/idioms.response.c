static inline int get_channel(int channel)
{
  return (channel & 1) * 4 + 112;
}