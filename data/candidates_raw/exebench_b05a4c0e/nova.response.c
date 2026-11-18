static void func0(int *out, int in, const struct biquad2_params *biq,
		     const int *in_buf)
{
	int i, mem[2];

	mem[0] = in / (biq->a1 * biq->a2);
	mem[1] = in - biq->a1 * mem[0] * biq->b1 - biq->a2 * mem[0] * biq->b2;

	for (i = 0; i < 4; i++)
		out[i] = (in_buf[i] << 1) + mem[i % 2];
}