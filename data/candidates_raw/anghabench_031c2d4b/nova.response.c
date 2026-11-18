static int func0(unsigned char c)
{
	unsigned char is_127_or_128;
	unsigned char is_space;

	is_space = (c == 0x00);
	is_127_or_128 = (c == 0x7f) || (c >= 0x80);

	return (is_space || is_127_or_128);
}