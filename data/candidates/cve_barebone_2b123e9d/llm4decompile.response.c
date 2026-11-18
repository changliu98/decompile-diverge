int
writefile(const char *name, string *s)
{
	FILE *f;
	int ret;

	if ((f = fopen(name, "w")) == NULL) {
		warn("open %s:", name);
		return -1;
	}
	ret = 0;
	if (fwrite(s->s + 1, 1, s->n, f) != s->n || fflush(f)) {
		warn("write %s:", name);
		ret = -1;
	}
	fclose(f);
	return ret;
}