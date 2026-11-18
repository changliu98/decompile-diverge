int
persistent_cache_read_entry_v3(rdpPersistentCache* persistent, PERSISTENT_CACHE_ENTRY* entry)
{
    PERSISTENT_CACHE_ENTRY_V3 entry3;
    memset(&entry3, 0, sizeof(entry3));
    do { if (!(persistent)) { __assert_fail("persistent", "/work/harness.c", 279, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)"); } } while (0);
    do { if (!(entry)) { __assert_fail("entry", "/work/harness.c", 280, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)"); } } while (0);

    if (fread(&entry3, sizeof(entry3), 1, persistent->fp) != 1)
        return -1;

    entry->key64 = entry3.key64;
    entry->width = entry3.width;
    entry->height = entry3.height;

    size_t size = (size_t)(entry->width * entry->height * 4);

    if (size > 0xFFFFFFFF)
        return -1;

    entry->flags = 0;

    if (size > persistent->bmpSize)
    {
        persistent->bmpSize = size;
        BYTE* new_data = winpr_aligned_recalloc(persistent->bmpData, persistent->bmpSize, 1, 32);

        if (new_data == NULL)
            return -1;

        persistent->bmpData = new_data;
    }

    entry->size = (UINT32)size;
    entry->data = persistent->bmpData;

    if (fread(entry->data, entry->size, 1, persistent->fp) != 1)
        return -1;

    return 1;
}