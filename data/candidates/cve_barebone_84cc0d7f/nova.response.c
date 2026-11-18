static void faad_resetbits(struct bitstr *bs, int bits)
{
	unsigned int n = bits >> 5;
	unsigned int m = bits & 0x1f;
	unsigned int v;

	bs->bitpos -= bits;
	if (bs->bitpos >= 4) {
		v = get_u32(bs->cur - n);
		bs->bitpos -= 4;
	} else {
		v = get_u32(bs->cur - n);
		bs->bitpos = 0;
	}
	bs->cur -= n;

	if (bs->bitpos >= 4) {
		v = (v << m) | get_u32(bs->cur - 1);
		bs->bitpos -= 4;
	} else {
		v = (v << m) | get_u32(bs->cur - 1);
		bs->bitpos = 0;
	}
	bs->val = v;
	bs->size = (n + 1) << 2;
	bs->cur -= n + 1;
	bs->nbytes = 0;
}