int strip_trailing_slashes(char *file)
{
	char *base = last_component(file);
	size_t len;
	int had_slash;

	if (!*base)
		base = file;
	len = base_len(base);
	had_slash = base[len] != '\0';
	base[len] = '\0';
	return had_slash;
}