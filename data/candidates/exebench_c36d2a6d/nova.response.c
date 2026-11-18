static inline int epindex_to_epnum(int index, int *blk)
{
	int blk_index = index % 2;

	if (blk)
		*blk = blk_index;

	return (index + blk_index) / 2;
}