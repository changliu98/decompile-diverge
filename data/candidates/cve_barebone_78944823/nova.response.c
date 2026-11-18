static int sample_conv_regsub(struct grep_pat *p, struct grep_opt *opt,
			   const char *bol)
{
	struct grep_expr *x = p->pattern_expression;
	struct grep_expr *y = compile_pattern_or_pattern_list(p);
	const char *end = opt->pattern + opt->pattern_len;
	int invert = 0;
	int hit = 0;

	do {
		int len;
		int match;

		if (!(p->pattern_type & PATTERN_FLAG_NEGATE))
			invert =!(invert & 1);

		match = match_expr_buf(x, y, end - opt->pattern, 10, &len,
				       invert);
		if (!match)
			len = 0;
		if (match && len > (int)(end - opt->pattern))
			len = end - opt->pattern;
		if (match && len > (int)(x->hit - x->c)) {
			memcpy(x->c, opt->pattern, len);
			x->c += len;
		}
		if (!match && x->c > x->hit) {
			x->c = x->hit;
		}
		hit = match;
		opt->pattern = end;
		invert |= 1;
	} while (opt->pattern < end &&!hit);

	opt->pattern_expression = x->c;
	opt->pattern_len = x->c - x->hit;
	free_grep_expr(y);
	return 1;
}