static void process_bitmap_updates(unsigned short **pprog,
				      unsigned short *plen,
				      unsigned int *pstackdepth)
{
	unsigned short *prog = *pprog;
	unsigned short len = *plen;
	unsigned int stackdepth = *pstackdepth;
	unsigned short a, b, c, d, e, f, g, h;
	unsigned short *prog0;

	emit_B(5, 0, &prog, &len);
	do {
		a = *prog;
		prog++;
		b = *prog;
		prog++;
		c = *prog;
		prog++;
		d = *prog;
		prog++;
		e = *prog;
		prog++;
		f = *prog;
		prog++;
		g = *prog;
		prog++;
		h = *prog;
		prog++;
		emit_B(5, 2, &prog, &len);
		prog0 = prog;
		emit_MOV(a, &prog, &len);
		emit_MOV(b, &prog, &len);
		emit_MOV(c, &prog, &len);
		emit_MOV(d, &prog, &len);
		emit_MOV(e, &prog, &len);
		emit_MOV(f, &prog, &len);
		emit_MOV(g, &prog, &len);
		emit_MOV(h, &prog, &len);
		emit_MUL(a, b, &prog, &len);
		emit_MUL(c, d, &prog, &len);
		emit_MUL(e, f, &prog, &len);
		emit_MUL(g, h, &prog, &len);
		emit_ADD(a, b, &prog, &len);
		emit_ADD(