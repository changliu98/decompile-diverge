static void func0(int *volume)
{
	if (*volume < 0)
		*volume = 0;
	else if (*volume > 100)
		*volume = 100;
}