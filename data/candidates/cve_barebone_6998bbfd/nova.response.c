static void process_bitmap_updates(unsigned short **pprog,
				  unsigned short *plen,
				  unsigned int *pflags)
{
	unsigned short *prog = *pprog;
	unsigned short len = *plen;
	unsigned short i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;
	unsigned short *prog_start;

	REPEAT(4,
		i = code_r(prog, pflags);
		j = code_r(prog, pflags);
		k = code_r(prog, pflags);
		l = code_r(prog, pflags);
		m = code_r(prog, pflags);
		n = code_r(prog, pflags);
		o = code_r(prog, pflags);
		p = code_r(prog, pflags);
		q = code_r(prog, pflags);
		r = code_r(prog, pflags);
		s = code_r(prog, pflags);
		t = code_r(prog, pflags);
		u = code_r(prog, pflags);
		v = code_r(prog, pflags);
		w = code_r(prog, pflags);
		x = code_r(prog, pflags);
		y = code_r(prog, pflags);
		z = code_r(prog, pflags);

		REPEAT(5,
			i = code_r(prog, pflags);
			j = code_r(prog, pflags);
			k = code_r(prog, pflags);
			l = code_r(prog, pflags);
			m = code_r(prog, pflags);
			n = code_r(prog, pflags);
			o = code_r(prog, pflags);
			p = code_r(prog, pflags);
			q