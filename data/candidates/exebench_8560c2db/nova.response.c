static int mc_bitcode(const float* table, float val)
{
	unsigned int i, mask;

	for (i = 0, mask = 0; i < 8; i++) {
		if (val > table[i])
			mask |= 1 << i;
	}

	return mask;
}