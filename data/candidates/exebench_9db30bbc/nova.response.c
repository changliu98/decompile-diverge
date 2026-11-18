char *stdimpl_strcpy(char *s, const char *ct)
{
	char c, *os = s;

	while ((c = *ct++))
		*s++ = c;
	return os;
}