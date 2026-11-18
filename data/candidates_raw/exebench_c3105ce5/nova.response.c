ssize_t func0(int fd, void *buf, size_t count)
{
	char *p = buf;
	ssize_t total = 0;

	while (count > 0) {
		ssize_t loaded = xread(fd, p, count);
		if (loaded <= 0) {
			total = loaded;
			break;
		}

		count -= loaded;
		p += loaded;
		total += loaded;
	}

	return total;
}