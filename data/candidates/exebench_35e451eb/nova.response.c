static void adjust_point(int *volume)
{
	if (*volume < 0)
		*volume = 0;
	else if (*volume > 100)
		*volume = 100;
}