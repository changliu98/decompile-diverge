static void func0(u32 *p, int x, int y, int c)
{
	u32 v = p[0];
	int i, j;

	for (i = 0; i < 2; i++) {
		u32 mask = (i == 1? (x? 1 : 2) : 0) | (y? 4 : 0) | (c? 8 : 0);
		u32 val = (v & ~mask) | ((mask << (i + 1)) & mask);

		p[i + 1] = val;
	}
}