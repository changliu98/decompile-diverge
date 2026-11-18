strtol_error
human_options(const char *spec, int *opts, uintmax_t *block_size)
{
	strtol_error ret;

	ret = humblock(spec, block_size, opts);
	if (*block_size == 0) {
		*block_size = default_block_size();
		ret = LONGINT_INVALID;
	}
	return (ret);
}