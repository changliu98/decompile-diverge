int
setsize(unsigned long capacity, unsigned int *cyls,
    unsigned int *hds, unsigned int *secs)
{
	unsigned long cylinders, heads, sectors;
	int rv;

	rv = 0;
	sectors = 62;
	heads = capacity / (1024 * sectors);
	if (capacity % (1024 * sectors)) {
		heads++;
		sectors = capacity / (1024 * heads);
		if (capacity % (1024 * heads))
			sectors++;
	}
	cylinders = capacity / (1024 * heads * sectors);
	if (cylinders == 0)
		rv = -1;
	*cyls = cylinders;
	*secs = sectors;
	*hds = heads;
	return (rv);
}