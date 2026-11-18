static u8 rtl8xxxu_gen1_channel_to_group(u8 channel) {
  if (channel < 4)
    return 0;
  else if (channel < 10)
    return 1;
  else
    return 2;
}