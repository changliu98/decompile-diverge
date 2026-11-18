char *func0(char *s, char old, char new)
{
	char *p;

	if (!s ||!*s)
		return s;
	p = s;
	for (;;) {
		p = strchr(p, old);
		if (!p)
			break;
		*p++ = new;
	}
	return s;
}