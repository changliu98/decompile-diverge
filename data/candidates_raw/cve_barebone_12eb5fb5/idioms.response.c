int persistent_cache_read_entry_v3(struct rdpPersistentCache *persistent, struct PERSISTENT_CACHE_ENTRY *entry)
{
    struct PERSISTENT_CACHE_ENTRY_V3 entryv3;
    unsigned long size;
    void *data;
    memset(&entryv3, 0, sizeof(entryv3));
    do { if (! (persistent)) { log_error("persistent", "/work/harness.c", 113, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)"); return (0); } } while (0);
    do { if (! (entry)) { log_error("entry", "/work/harness.c", 114, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)"); return (0); } } while (0);
    if (read_struct(&entryv3, sizeof(entryv3), 1, persistent->fp) != 1)
        return -1;
    entry->key64 = entryv3.key64;
    entry->width = entryv3.width;
    entry->height = entryv3.height;
    size = (unsigned long)entry->height * (unsigned long)entry->width * sizeof(uint32_t);
    if (size > (unsigned int)-1)
        return -1;
    entry->size = (unsigned int)size;
    if (entry->size > persistent->bmpSize)
    {
        persistent->bmpSize = entry->size;
        data = xrealloc(persistent->bmpData, persistent->bmpSize, 1, 32);
        if (!data)
            return -1;
        persistent->bmpData = data;
    }
    entry->data = (void *)persistent->bmpData;
    if (read_struct(entry->data, entry->size, 1, persistent->fp) != 1)
        return -1;
    return 1;
}