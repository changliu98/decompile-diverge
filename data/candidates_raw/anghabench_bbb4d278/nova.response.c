static void func0(unsigned int unichar,
				     unsigned char *utf8char)
{
	if (unichar <= 0x0d)
		utf8char[0] = unichar & 0xff;
	else if (unichar <= 0x84)
		utf8char[0] = 0x0e;
	else if (unichar <= 0xfe)
		utf8char[0] = 0x0f;
}