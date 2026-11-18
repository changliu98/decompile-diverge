static char *
strcpyend(char *dst, const char *src)
{
	while ((*dst++ = *src++)!= '\0')
		continue;
	return (dst - 1);
}