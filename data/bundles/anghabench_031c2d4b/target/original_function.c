bool tomoyo_invalid(const unsigned char c)
{
	return c && (c <= ' ' || c >= 127);
}