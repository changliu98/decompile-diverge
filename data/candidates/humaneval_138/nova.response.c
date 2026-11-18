static int func0(int off)
{
	int page;

	if ((off % 2) || (off < 0x8))
		page = 0;
	else
		page = 1;
	return page;
}