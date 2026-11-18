int rtl8xxxu_gen1_channel_to_group(int freq_channel)
{
	if (freq_channel < 4)
		return 0;
	if (freq_channel < 10)
		return 1;
	return 2;
}