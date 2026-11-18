static inline char *func0(char *str, char c)
{
	str = strchr(str, c);
	if (str)
		*str = '\0';
	return str;
}