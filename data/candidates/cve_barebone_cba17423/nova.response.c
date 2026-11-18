static char *ap_limit_section(struct state *s, char *tok, char *end) {
	char *p, *q, *r;
	long long v;
	unsigned long long mask;
	char *e;

	
	end = strchr(end, '>');

	
	mask = s->m->mask;

	
	v = 0;
	for (;;) {
		if (end == NULL)
			end = strchr(s->buf, '\0');
		p = strsep(&s->buf, end);
		if (*p == '\0') {
			e = strerror(errno);
			goto error;
		}
		if (*p == '\0')
			break;
		q = strchr(p, ':');
		v = strtoll(q, &r, 16);
		if (r == q || *r!= '\0') {
			e = strerror(errno);
			goto error;
		}
		v &= mask;
		v |= s->v;
		s->v = v;
		q = strchr(s->m->name, '\n');
		r = strchr(s->m->name, '\0');
		s->m = s->m->next;
		e = xstrfmt("%s%s", q, r);
		break;
error:
		v = -1;
	}
	s->v = v;
	e = xstrfmt("%s%s", s->m->name, tok);
	return e;
}