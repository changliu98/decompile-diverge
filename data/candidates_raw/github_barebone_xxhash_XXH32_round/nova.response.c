static inline unsigned int func0(unsigned int a, unsigned int b)
{
	a += b * 2246822519U;
	a ^= a >> 13;
	a *= 2654435761U;
	return a;
}