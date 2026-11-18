static int persistent_cache_read_entry_v3(rdpPersistentCache* persistent,
                                          PERSISTENT_CACHE_ENTRY* entry)
{
	PERSISTENT_CACHE_ENTRY_V3 entry3 = WINPR_C_ARRAY_INIT;

	WINPR_ASSERT(persistent);
	WINPR_ASSERT(entry);

	if (fread(&entry3, sizeof(entry3), 1, persistent->fp) != 1)
		return -1;

	entry->key64 = entry3.key64;
	entry->width = entry3.width;
	entry->height = entry3.height;
	const UINT64 size = 4ull * entry3.width * entry3.height;
	if (size > UINT32_MAX)
		return -1;
	entry->size = (UINT32)size;
	entry->flags = 0;

	if (entry->size > persistent->bmpSize)
	{
		persistent->bmpSize = entry->size;
		BYTE* bmpData = (BYTE*)winpr_aligned_recalloc(persistent->bmpData, persistent->bmpSize,
		                                              sizeof(BYTE), 32);

		if (!bmpData)
			return -1;

		persistent->bmpData = bmpData;
	}

	entry->data = persistent->bmpData;

	if (fread((void*)entry->data, entry->size, 1, persistent->fp) != 1)
		return -1;

	return 1;
}