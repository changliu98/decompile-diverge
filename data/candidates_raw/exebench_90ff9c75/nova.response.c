static void func0(unsigned int value, char *string)
{
	unsigned int digit;
	unsigned int i;

	i = value;
	string += 4;
	*string = 0;
	for (i = value; i > 0; i /= 16) {
		digit = i % 16;
		if (digit < 10)
			digit += '0';
		else
			digit += 'A'-10;
		*--string = digit;
	}
}