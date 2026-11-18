static size_t argmatch_exact(const char *name, const char *const *list)
{
	size_t i;
	for (i = 0; list[i]; i++)
		if (!strcmp(list[i], name))
			return i;
	return -1;
}