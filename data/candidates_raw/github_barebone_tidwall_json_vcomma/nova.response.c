static int func0(const char *line, long size, long pos)
{
	long i;

	if (pos == size)
		i = -1 - pos;
	else if (line[pos] == ',')
		i = pos;
	else
		for (i = pos; i < size; i++) {
			unsigned char c = line[i];
			switch (c) {
			case'': case '\t': case '\r': case '\n':
				continue;
			case ',':
				i = pos;
				goto found;
			default:
				if (c == '!' || c == '-' || c == '+') {
					i = pos;
					goto found;
				}
				for (i = pos; i < size; i++) {
					c = line[i];
					if (c == line[pos])
						goto found;
				}
				i = -1 - pos;
				goto found;
			}
		}
	i = -1 - pos;
found:
	return i;
}