static inline u32 func0(u32 a, u32 b, u32 c, u32 d)
{
	u32 x, y, z, w;
	u32 i = b ^ c ^ d;
	u32 j = a ^ b ^ c;
	u32 k = a ^ c ^ d;
	u32 l = a ^ b ^ d;

	x = (i & 1) * (j & 2) * (k & 4) * (l & 8);
	y = (i & 2) * (j & 4) * (k & 8) * (l & 1);
	z = (i & 4) * (j & 8) * (k & 1) * (l & 2);
	w = (i & 8) * (j & 1) * (k & 2) * (l & 4);

	return x | y | z | w;
}