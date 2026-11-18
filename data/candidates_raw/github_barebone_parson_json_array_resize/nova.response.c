static int func0(struct tep_handle *tep, unsigned long long size)
{
	char *buf = NULL;
	int ret = -1;

	if (size == 0)
		ret = -1;
	else {
		buf = malloc(size);
		if (buf == NULL)
			ret = -1;
		else {
			if (tep->cmdlines && tep->cmdline_size > 0)
				memcpy(buf, tep->cmdlines, tep->cmdline_size);
			free(tep->cmdlines);
			tep->cmdlines = buf;
			tep->cmdline_size = size;
			ret = 0;
		}
	}

	return ret;
}