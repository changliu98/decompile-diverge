char *truncate_string_at_char(char *s, char c)
{
	char *p = NULL;

	for (p = s; ; p++) {
		switch (*p) {
		case '\0':
			return s;
		case c:
			*p = '\0';
			return s;
		}
	}
}