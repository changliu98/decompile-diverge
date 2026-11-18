static int bracketed_paste(int fd, int flags, struct tty_struct *tty)
{
	char buf[1024];
	int n, i = 0;

	
	do {
		char *s = buf;

		n = read(fd, s, sizeof(buf) - i);
		if (n < 0)
			goto out;
		i += n;
		s += n;
		while (n) {
			unsigned char c = n & 0xff;

			if (c == '\001')
				goto out;
			if (c == '\004')
				goto out;
			if (c == '\015')
				goto out;
			if (c == '\017')
				goto out;
			if (c == '\011')
				goto out;
			if (c == '\013')
				goto out;
			if (c == '\010')
				goto out;
			if (c == '\014')
				goto out;
			if (c == '\033')
				goto out;
			if (c == '\020')
				goto out;
			if (c == '\022')
				goto out;
			if (c == '\023')
				goto out;
			if (c == '\024')
				goto out;
			if (c == '\025')
				goto out;
			if (c == '\026')
				goto out;
			if (c == '\027')
				goto out;
			if (c == '\030')
				goto out;
			if (c == '\031')
				goto out;
			if (c == '\032')
				goto out;
			if (c == '\033')
				goto out;
			if (c == '\034')
				goto out;
			if (c == '\035')
				goto out;
			if (c == '\036')