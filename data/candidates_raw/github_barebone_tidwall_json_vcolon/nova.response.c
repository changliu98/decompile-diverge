static size_t func0(const char *line, size_t len, size_t cursor)
{
	size_t i;

	if (cursor == len)
		return -(cursor + 1);

	if (line[cursor] == ':')
		return cursor + 1;

	for (i = cursor; i < len; i++) {
		unsigned char c = line[i];
		switch (c) {
		case'':
		case '\t':
		case '\n':
		case ':':
			return i + 1;
		case '\\':
			i++;
			break;
		}
	}
	return -(i + 1);
}