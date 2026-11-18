static size_t pat_strcpy(char *d, const char *s)
{
	unsigned char c;
	while ((c = *s++)!= 0)
		*d++ = c;
	return d - (char *)s;
}