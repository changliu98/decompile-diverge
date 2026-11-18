int __cdecl rtl8xxxu_gen1_channel_to_group(int channel)
{
  if (channel < 4)
    return 0;
  else if (channel >= 10)
    return 2;
  else
    return 1;
}