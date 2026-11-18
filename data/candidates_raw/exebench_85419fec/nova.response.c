static char *
func0(char *dst, const char *src)
{
	while ((*dst++ = *src++)!= '\0')
		continue;
	return (dst - 1);
}