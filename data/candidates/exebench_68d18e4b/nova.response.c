static void SwitchToChar(char *out, unsigned char val)
{
	if (val / 16 >= 10)
		out[0] = 'A' + val / 16 - 10;
	else
		out[0] = '0' + val / 16;

	if (val % 16 >= 10)
		out[1] = 'A' + val % 16 - 10;
	else
		out[1] = '0' + val % 16;
}