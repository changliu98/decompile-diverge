int func0(int fd, char *buf, size_t buflen)
{
	char *out = buf;
	size_t outlen = buflen;

	while (outlen > 0) {
		ssize_t ret;

		ret = read(fd, out, outlen);
		if (ret <= 0) {
			int rc = ret? -1 : 0;
			return rc;
		}

		outlen -= ret;
		out += ret;
	}

	return out - buf;
}