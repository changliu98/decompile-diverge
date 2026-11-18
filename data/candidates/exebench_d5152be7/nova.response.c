static int sdram_convert(unsigned int freq,
				   enum clock_set_flags flags)
{
	unsigned int dfs_freq;
	unsigned int dfs_div;

	dfs_freq = 1000000000;
	dfs_div = dfs_freq / freq;
	dfs_div = (dfs_div / 25) + 1;
	if (dfs_div > 255)
		dfs_div = 255;

	*(u8 *)flags = dfs_div;

	return 0;
}