char *func0(char *s, char old, char new)
{
	char *p;

	for (p = s; p; p++) {
		if (*p == 0)
			break;
		if (*p == old)
			*p = new;
	}
	return s;
}