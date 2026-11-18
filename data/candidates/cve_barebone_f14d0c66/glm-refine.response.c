int __cdecl persistent_cache_read_entry_v3(rdpPersistentCache *persistent, PERSISTENT_CACHE_ENTRY *entry)
{
  PERSISTENT_CACHE_ENTRY_V3 entry3;
  UINT64 size;

  memset(&entry3, 0, sizeof(entry3));

  // Validate arguments
  if (!persistent)
    __assert_fail("persistent", "/work/harness.c", 0x117u, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)");
  if (!entry)
    __assert_fail("entry", "/work/harness.c", 0x118u, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)");

  // Read the 12-byte V3 cache entry header
  if (fread(&entry3, 0xCuLL, 1uLL, persistent->fp) != 1)
    return -1;

  // Map V3 entry fields to the standard cache entry
  entry->key64 = entry3.key64;
  entry->width = entry3.width;
  entry->height = entry3.height;

  // Calculate bitmap size (width * height * 4 bytes per pixel)
  size = (UINT64)entry3.height * 4LL * entry3.width;
  if (size > 0xFFFFFFFF)
    return -1;

  entry->flags = 0;

  // Reallocate persistent bitmap buffer if the new entry is larger
  if (size > persistent->bmpSize)
  {
    BYTE *bmpData;

    persistent->bmpSize = size;
    
    // The decompiler incorrectly identified this as a constructor. 
    // Based on the arguments, it is clearly an aligned memory reallocator (e.g. _aligned_realloc).
    bmpData = (BYTE *)_aligned_realloc(persistent->bmpData, persistent->bmpSize, 0x20uLL);
    if (!bmpData)
      return -1;

    persistent->bmpData = bmpData;
  }

  entry->size = size;
  entry->data = persistent->bmpData;

  // Read the bitmap data into the (potentially reallocated) buffer
  if (fread(entry->data, entry->size, 1uLL, persistent->fp) != 1)
    return -1;

  return 1;
}