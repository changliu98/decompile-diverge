static size_t func0(char *d, const char *s)
{
	unsigned char c;
	while ((c = *s++)!= 0)
		*d++ = c;
	return d - (char *)s;
}