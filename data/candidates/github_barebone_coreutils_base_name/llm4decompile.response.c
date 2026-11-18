char *base_name(const char *name)
{
	const char *base = last_component(name);
	char *result;
	idx_t len;

	if (*base == '\0') {
		base = name;
		len = base_len(name);
	} else {
		len = base_len(base);
		if (base[len] == '/')
			len++;
	}

	result = ximalloc(len + 1);
	memcpy(result, base, len);
	result[len] = '\0';
	return result;
}