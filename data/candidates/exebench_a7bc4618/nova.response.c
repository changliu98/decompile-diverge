static inline char *remove_line_ending(char *str, char c)
{
	str = strchr(str, c);
	if (str)
		*str = '\0';
	return str;
}