static void func0(unsigned int a, unsigned int b,
			     unsigned int *high, unsigned int *low)
{
	unsigned int a0 = a & 0xffff;
	unsigned int a1 = a >> 16;
	unsigned int b0 = b & 0xffff;
	unsigned int b1 = b >> 16;
	unsigned int z0 = a0 * b0;
	unsigned int z1 = a1 * b0;
	unsigned int z2 = a0 * b1;
	unsigned int z3 = a1 * b1;
	unsigned int z4 = (z3 << 16) + z2;

	z2 += (z1 << 16) + z0;
	z1 += z0 >> 16;
	z0 += (z3 << 16) + z2;
	z4 += (z2 >> 16) + z1;
	z0 += (z4 >> 16);
	z4 <<= 16;

	*low = z0;
	*high = z4;
}