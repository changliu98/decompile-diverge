static void TEA_transform(u32 *a, u32 *b)
{
	u32 a0 = a[0], a1 = a[1], b0 = b[0], b1 = b[1], b2 = b[2];
	int n = 16;

	do {
		a0 += b0 + ((a1 + b1) ^ (a1 + b1 >> 5) ^ ((a1 + b1) << 4));
		a1 += b2 + ((a0 + b0) ^ (a0 + b0 >> 5) ^ ((a0 + b0) << 4));
	} while (--n);

	a[0] += a0;
	a[1] += a1;
}