char *
build_ustar_entry_name(char *dest, const char *src, size_t src_length,
    const char *insert)
{
	const char *filename_end;
	const char *filename;
	const char *prefix_end;
	const char *prefix;
	const char *suffix_end;
	const char *suffix;
	size_t maxlen;
	size_t insert_length;
	int need_slash;

	maxlen = 99;
	if (insert != NULL)
		insert_length = strlen(insert) + 2;
	else
		insert_length = 0;

	if (src_length < maxlen && insert == NULL) {
		strncpy(dest, src, src_length);
		dest[src_length] = '\0';
		return (dest);
	}

	need_slash = 0;
	filename_end = src + src_length;
	while (filename_end > src && filename_end[-1] == '/') {
		filename_end--;
		need_slash = 1;
	}
	if (filename_end > src + 1 && filename_end[-1] == '.'
	    && filename_end[-2] == '/') {
		filename_end -= 2;
		need_slash = 1;
	}
	if (need_slash)
		maxlen = 98;

	filename = filename_end;
	while (filename > src && filename[-1] != '/')
		filename--;
	if (filename[0] == '/' && filename < filename_end - 1)
		filename++;

	if (filename + (maxlen - insert_length) < filename_end)
		filename_end = filename + (maxlen - insert_length);

	prefix_end = src + 155;
	if (prefix_end > filename)
		prefix_end = filename;
	while (prefix_end > src && prefix_end[-1] != '/')
		prefix_end--;
	if (prefix_end < filename && prefix_end[0] == '/')
		prefix_end++;

	suffix_end = prefix_end + ((maxlen - insert_length)
	    - (filename_end - filename));
	if (suffix_end > filename)
		suffix_end = filename;
	if (suffix_end < prefix_end)
		suffix_end = prefix_end;
	while (suffix_end > prefix_end && suffix_end[-1] != '/')
		suffix_end--;
	if (suffix_end < filename && suffix_end[0] == '/')
		suffix_end++;

	suffix = suffix_end;
	prefix = prefix_end;
	if (prefix < prefix_end) {
		strncpy(dest, prefix, prefix_end - prefix);
		dest += prefix_end - prefix;
	}
	if (suffix < suffix_end) {
		strncpy(dest, suffix, suffix_end - suffix);
		dest += suffix_end - suffix;
	}
	if (insert != NULL) {
		strcpy(dest, insert);
		dest += strlen(insert);
		*dest++ = '/';
	}
	strncpy(dest, filename, filename_end - filename);
	dest += filename_end - filename;
	if (need_slash)
		*dest++ = '/';
	*dest = '\0';
	return (dest);
}