static void basename_discriminant(char *path, size_t *len, size_t *files)
{
	char *base = strrchr(path, '/');

	if (!base)
		base = path;
	else
		base++;

	*len = 0;
	*files = 0;

	while (*base) {
		*len *= 33;
		*len += *base++;
		(*files)++;
	}
}