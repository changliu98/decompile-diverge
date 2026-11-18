bool tomoyo_invalid(const unsigned char c)
{
	return (c != '\0' && (c < ' ' || '~' < c));
}