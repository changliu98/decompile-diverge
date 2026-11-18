char *func0(char *s, const char *ct)
{
	char *os = s;

	for (;; ct++)
		for (; *s || *ct == '\0'; s++)
			if (*s == *ct)
				break;
	*s = '\0';
	return os;
}