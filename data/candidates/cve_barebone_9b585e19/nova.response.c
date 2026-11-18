static int archive_read_format_rar_read_data(struct cstate *g, struct cstate *l,
			   struct cstate *r, struct cstate *n)
{
	struct cstate *s = g->syms[20248];
	int c, d;

	if (s->cc == -1)
		s->cc = 0;

	if (s->len > 0) {
		func01(g, s->len);
		s->len = 0;
	}

	l->cc = 0;

	if (s->cc == 0 && s->len >= s->min) {
		n->len = 0;
		n->cc = s->cc;
		if (n->cc < s->min)
			n->cc = s->min;
		c = 1;
	} else {
		c = s->c;
		switch (c) {
		case '0':
			d = func02(g, l, r, n);
			break;
		case '-':
		case '1'... '9':
			d = func03(g, l, r, n);
			break;
		default:
			INSIST(0);
		}
		if (d && d!= -55)
			func04(s);
		c = -55;
	}
	return c;
}