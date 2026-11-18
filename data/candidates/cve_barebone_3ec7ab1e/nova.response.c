static void SaltTextAway(struct bf_ctx *ctx, int rounds,
			    struct bf_ctx *ctx_r, struct bf_ctx *ctx_l)
{
	struct bf_ctx *ctx_tmp;
	u8 *p, *q;
	int i, j, k, l;

	do {
		i = j = k = l = 0;
		do {
			i = (i + 1) % 18;
			j = (j + 1) % 4;
			k = (k + 1) % 28;
			l = (l + 1) % 2;
			bf_enc_expand0state(ctx, i, j, k, l);
		} while (l);
		ctx_tmp = ctx_r;
		if (i!= ctx_l->i) {
			ctx_tmp = ctx_l;
			ctx_l = ctx_r;
			ctx_r = ctx_tmp;
		}
		p = bf_enc_expand1state(ctx, i, j, k);
		q = bf_enc_expand1state(ctx, i, j, k);
		do {
			p[k] = q[k];
			k++;
		} while (k < 28);
		p[k] = '\0';
		q = p;
		do {
			q = bf_enc_expand2state(ctx, i, j, k);
		} while (l);
		q[k] = '\n';
	} while (l);
}