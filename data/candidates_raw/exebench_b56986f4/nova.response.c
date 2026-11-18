static void func0(u32 width, u8 *table)
{
	u32 w = width;
	u32 v;
	u32 i;
	u32 j;

	table[8] = 0;
	table[9] = 16;

	for (i = 2; w > 32; w >>= 2) {
		v = (w >> 3) * 8;
		for (j = i; j < i + v; j++) {
			table[j] = (j - i) * 4;
			table[j + v] = table[j] + (w >> 2);
		}
		i += v;
	}
}