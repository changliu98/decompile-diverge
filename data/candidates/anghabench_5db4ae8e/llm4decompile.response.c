u8 rtl8xxxu_gen1_channel_to_group(u8 channel)
{
	u8 group;

	if (channel <= 3)
		group = 0;
	else if (channel <= 9)
		group = 1;
	else
		group = 2;

	return group;
}