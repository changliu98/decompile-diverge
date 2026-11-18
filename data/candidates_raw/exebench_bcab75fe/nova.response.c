static bool func0(unsigned int count, unsigned int max_count,
			    unsigned int *new_count)
{
	unsigned int old_count = 0;

	*new_count = count * max_count;

	if (*new_count < old_count)
		return false;

	return true;
}