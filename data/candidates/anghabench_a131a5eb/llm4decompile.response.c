uint32_t lzma_get_dist_state(uint32_t len)
{
	uint32_t state;

	if (len >= MATCH_LEN_MIN + DIST_STATES)
		state = DIST_STATES - 1;
	else
		state = len - MATCH_LEN_MIN;

	return state;
}