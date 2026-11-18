static int FileSwfDecompression(const unsigned char *in, unsigned int inlen,
		       unsigned char *out, struct sha1_state *sctx,
		       unsigned int digestsize, unsigned int block_size,
		       unsigned int pad_size)
{
	unsigned int left, opad_size, ipad_size, i, j;
	unsigned char tmp[256];
	int ret = 0;

	left = HASH_LEN(in, inlen);
	if (left == 1) {
		i = 0;
	} else {
		i = left;
		memset(out, 0, 1);
	}

	if (left == 2)
		i = 8;
	else if (left == 3)
		i = 17;

	if (inlen > i)
		memcpy(out, in, i);
	else
		memcpy(out, in, inlen);

	left = HASH_LEN(out, i);

	if (left == 2 && digestsize == 3)
		i += 13;

	while (1) {
		memcpy(tmp, out, i);
		memset(tmp + i, 0xff, pad_size - i);
		tmp[pad_size - 1] = digestsize;
		tmp[pad_size - 2] = sctx->state[0];
		tmp[pad_size - 3] = sctx->state[1];
		tmp[pad_size - 4] = sctx->state[2];
		tmp[pad_size - 5] = sctx->state[3];
		tmp[pad_size - 6] = sctx->state[4];

		ret = sha1_vector(1, &tmp, pad_size, sctx);
		if (ret)
			break;
		ret = 0;
	}

	return ret;
}