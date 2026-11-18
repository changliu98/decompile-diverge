unsigned int ad7192_get_temp_scale(bool unipolar)
{
	return unipolar ? 2815 * 2 : 2815;
}