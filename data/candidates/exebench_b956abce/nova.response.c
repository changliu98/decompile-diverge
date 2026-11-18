static void
set_page_data(int i, void *data)
{
	uint64_t *umax = data;
	uint64_t max = i;

	*umax = max;
}