static struct symbol *xf_Pointer_get_window(const struct s_s *s)
{
	struct symbol *sp;

	if (s == 0) {
		eq_insert(EQ_GLOBAL, 0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0);
		sp = 0;
	} else if (s->type == 0) {
		eq_insert(EQ_GLOBAL, 0, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7);
		sp = 0;
	} else if (s->ref == 0) {
		eq_insert(EQ_GLOBAL, 0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0);
		sp = 0;
	} else {
		sp = s->ref->x.symbol;
	}
	return sp;
}