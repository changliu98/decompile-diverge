static void bitmap_set(void *table, uint64_t offset, uint64_t size)
{
	uint64_t *entries;
	uint64_t entry, mask, index, shift;

	entries = table;
	index = offset / 64;
	entry = index;
	shift = 64 - (offset % 64);
	mask = (uint64_t)-1 << (offset % 64);

	while (size > 0) {
		if (size >= (64 - shift)) {
			entries[index] |= mask;
			size -= (64 - shift);
			mask = (uint64_t)-1;
			shift = 64;
			index++;
		} else {
			if (offset % 64)
				mask = (1ULL << (size % 64)) - 1;
			else
				mask = (uint64_t)-1;
			entries[index] |= mask;
			break;
		}
	}
}