unsigned int sgl_len(unsigned int n)
{
	return 2 + ((n - 1) >> 1) + ((n - 1) & 1);
}