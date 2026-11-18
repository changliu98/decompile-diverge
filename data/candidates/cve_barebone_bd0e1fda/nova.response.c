static long njs_vmcode_array(struct vdso_elfinfo *e, const char *name)
{
	const char *s;
	unsigned long v;
	long ret;

	s = (const char *)find_symbol(e, (const char *)0, name, 8);
	if (s && (((unsigned long)s) & 1)) {
		unsigned char *p = (unsigned char *)s;
		if (p[8]) {
			unsigned char *q = p + 8;
			v = *q++;
			do {
				v <<= 7;
				v += (*q & 0x7f);
				if (!(*q & 0x80))
					break;
			} while (++q < (unsigned char *)s + 16);
			ret = (long)v;
		} else
			ret = (long)strtoul(s, NULL, 0);
		memcpy((void *)s, &ret, sizeof(ret));
		ret = (long)sizeof(ret);
	} else
		ret = -1L;
	return ret;
}