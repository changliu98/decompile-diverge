int __cdecl persistent_cache_read_entry_v3(rdpPersistentCache *persistent, PERSISTENT_CACHE_ENTRY *entry)
{
  PERSISTENT_CACHE_ENTRY_V3 entry3;
  UINT64 size;
  BYTE *bmpData;

  memset(&entry3, 0, sizeof(entry3));

  if (!persistent)
    __assert_fail("persistent", "/work/harness.c", 0x71u, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)");
  if (!entry)
    __assert_fail("entry", "/work/harness.c", 0x72u, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)");

  // Read the 12-byte V3 cache entry header
  if (fread(&entry3, 0xCuLL, 1uLL, persistent->fp) != 1)
    return -1;

  entry->key64 = entry3.key64;
  entry->width = entry3.width;
  entry->height = entry3.height;

  // Calculate bitmap size: width * height * 4 (32bpp)
  size = (UINT64)entry3.height * 4LL * entry3.width;
  if (size > 0xFFFFFFFF)
    return -1;

  entry->size = (UINT32)size;

  // Reallocate persistent bitmap buffer if the current entry is larger
  if (entry->size > persistent->bmpSize)
  {
    persistent->bmpSize = entry->size;
    bmpData = (BYTE *)winpr_aligned_recalloc(persistent->bmpData, persistent->bmpSize, 1uLL, 0x20uLL);
    if (!bmpData)
      return -1;
    persistent->bmpData = bmpData;
  }

  entry->data = persistent->bmpData;

  // Read the bitmap data
  if (fread(entry->data, entry->size, 1uLL, persistent->fp) == 1)
    return 1;
  else
    return -1;
}