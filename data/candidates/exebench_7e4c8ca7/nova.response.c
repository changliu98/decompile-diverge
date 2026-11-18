void change_bit(int i, bits64 a)
{
	int eq;
	bits64 x;

	x = a;
	eq = ((x & 0x01) == 0);
	x = rightShift64(x, 1);
	if (eq) {
		x = x & 0x7FFFFFFFFFFFFFFF;
	} else {
		x = (x | 0x8000000000000000ULL);
	}
	bits64_s[i] = x;
}