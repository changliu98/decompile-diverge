int
parse_device(dev_t *dev, struct archive *a, const char *val)
{
	int		argc;
	char		*fmt;
	char		*p;
	char		*error;
	dev_t		d;
	unsigned long	numbers[3];
	dev_t		(*pack)(int, unsigned long *, char **);

	memset(dev, 0, sizeof(*dev));
	fmt = (char *)val;
	p = strchr(fmt, ',');
	if (p == NULL) {
		/*
		 * This is a raw device number.
		 */
		d = mtree_atol(&fmt);
	} else {
		*p++ = '\0';
		pack = pack_find(fmt);
		if (pack == NULL) {
			archive_set_error(&a->archive, 22,
			    "Unknown format `%s'", fmt);
			return (-20);
		}
		argc = 0;
		error = NULL;
		while ((fmt = la_strsep(&p, ",")) != NULL) {
			if (*fmt == '\0') {
				archive_set_error(&a->archive, 22,
				    "Missing number");
				return (-20);
			}
			numbers[argc++] = mtree_atol(&fmt);
			if (argc >= 4) {
				archive_set_error(&a->archive, 22,
				    "Too many arguments");
				return (-20);
			}
		}
		if (argc < 2) {
			archive_set_error(&a->archive, 22,
			    "Not enough arguments");
			return (-20);
		}
		d = pack(argc, numbers, &error);
		if (error != NULL) {
			archive_set_error(&a->archive, 22, "%s", error);
			return (-20);
		}
	}
	*dev = d;
	return (0);
}