int persistent_cache_read_entry_v3(struct rdpPersistentCache *persistent, struct PERSISTENT_CACHE_ENTRY *entry)
{
    struct PERSISTENT_CACHE_ENTRY_V3 entryv3;
    unsigned long size;
    memset(&entryv3, 0, sizeof(entryv3));
    do { if (!persistent) rdp_assert_msg("persistent", "/work/harness.c", 279, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)"); if (!entry) rdp_assert_msg("entry", "/work/harness.c", 280, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)"); } while (0);
    if (read_struct(&entryv3, sizeof(entryv3), 1, persistent->fp) != 1)
    {
        return -1;
    }
    entry->key64 = entryv3.key64;
    entry->width = entryv3.width;
    entry->height = entryv3.height;
    size = entry->width * entry->height * 4;
    if (size > (0x7fffffff * 2 + 1))
    {
        return -1;
    }
    entry->flags = 0;
    if (size > persistent->bmpSize)
    {
        unsigned char *data;
        persistent->bmpSize = size;
        data = (unsigned char *)rdp_realloc(persistent->bmpData,
                                             persistent->bmpSize,
                                             1,
                                             32);
        if (!data)
        {
            return -1;
        }
        persistent->bmpData = data;
    }
    entry->size = size;
    entry->data = (unsigned char *)persistent->bmpData;
    if (read_struct(entry->data, entry->size, 1, persistent->fp) != 1)
    {
        return -1;
    }
    return 1;
}