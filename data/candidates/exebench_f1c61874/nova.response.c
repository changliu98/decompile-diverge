static void squeeze(struct fpu *fpu)
{
	unsigned int i;
	unsigned int c = 0;

	for (i = 0; i < 32; i++) {
		c += fpu->fprs[i];
		fpu->fprs[i] = c & 0xff;
		c >>= 8;
	}

	c += fpu->fprs[32];
	fpu->fprs[32] = c & 0x7f;
	c = 19 * (c >> 7);

	for (i = 0; i < 32; i++) {
		c += fpu->fprs[i];
		fpu->fprs[i] = c & 0xff;
		c >>= 8;
	}

	fpu->fprs[32] += c;
}