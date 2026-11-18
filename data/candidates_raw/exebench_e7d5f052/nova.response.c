static void func0(unsigned char *a, unsigned char *b)
{
	unsigned char a_msb = *a;
	unsigned char b_msb = *b;
	unsigned char a_sign = a_msb >= 0xa1;
	unsigned char b_sign = b_msb >= 0xa1;
	unsigned char sign;
	unsigned char delta;
	unsigned char abs_a;
	unsigned char abs_b;

	sign = a_sign ^ b_sign;
	delta = (a_msb >= 0x80) - (b_msb >= 0x80);
	abs_a = a_msb - (a_msb >= 0x80);
	abs_b = b_msb - (b_msb >= 0x80);

	if (sign)
		*b = (abs_b - abs_a - delta) * 2 + sign;
	else
		*b = (abs_b - abs_a + delta) * 2;
	*a = a_msb - b_msb;
}