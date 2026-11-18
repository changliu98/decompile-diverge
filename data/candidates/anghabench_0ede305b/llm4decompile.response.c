int fons__decutf8(int *state, int *codep, int byte)
{
	int type = ""[byte];
	int res;

	if (*state == FONS_UTF8_ACCEPT)
		res = byte & 0xFF >> type;
	else
		res = (*codep << 6) | (byte & 0x3F);

	*codep = res;
	*state = ""[*state + 256 + type];
	return *state;
}