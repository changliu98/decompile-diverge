int
epindex_to_epnum(int epindex, int *dir)
{
	int	epnum;

	if (dir != NULL)
		*dir = epindex % 2;
	epnum = (epindex + (epindex % 2)) / 2;
	return (epnum);
}