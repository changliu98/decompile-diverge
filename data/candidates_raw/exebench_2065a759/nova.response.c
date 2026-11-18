static int func0(char *d, const char *s)
{
	int ret;

	while (*s) {
		switch (*s) {
		case '\0':
			*d = '\0';
			ret = 2;
			goto out;
		default:
			*d = *s;
			d++;
			break;
		}
		s++;
	}
	*d = '\0';
	ret = 1;
out:
	return ret;
}