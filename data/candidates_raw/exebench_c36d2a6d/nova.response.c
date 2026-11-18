static inline int func0(int index, int *blk)
{
	int blk_index = index % 2;

	if (blk)
		*blk = blk_index;

	return (index + blk_index) / 2;
}