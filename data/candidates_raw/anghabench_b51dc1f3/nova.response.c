int func0(int c)
{
	int l;

	if (c < 0 || c >= 0x80)
		l = -1;
	else
		l = utf8_1byte_cases[c];
	return l;
}