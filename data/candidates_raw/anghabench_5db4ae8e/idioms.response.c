int get_channel_type(int channel)
{
  if (channel < 4)
    return 0;
  if (channel < 10)
    return 1;
  return 2;
}