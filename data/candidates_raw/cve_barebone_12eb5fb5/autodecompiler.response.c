static int persistent_cache_read_entry_v3(rdpPersistentCache *persistent, PERSISTENT_CACHE_ENTRY_V3 *entry)
{
 int status;
 size_t size;
 char *buffer;
 PERSISTENT_CACHE_ENTRY_V3 header;

 memset(&header, 0, sizeof(header));

 do { if (!(persistent)) ___assert_fail("persistent", "harness.c", 113, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY_V3 *);"); } while (0);
 do { if (!(entry)) ___assert_fail("entry", "harness.c", 114, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY_V3 *);"); } while (0);

 if (fread(&header, sizeof(header), 1, persistent->cacheFile) != 1)
 {
  status = -1;
 }
 else
 {
  entry->key64 = header.key64;
  entry->width = header.width;
  entry->height = header.height;

  size = entry->width * 4 * entry->height;

  if (size > ((size_t)(-1)))
  {
   status = -1;
  }
  else
  {
   entry->size = (unsigned int) size;
   entry->offset = 0;

   if (entry->size > persistent->bitmapCacheBitmapDataSize)
   {
    persistent->bitmapCacheBitmapDataSize = entry->size;
    buffer = (char *) winpr_aligned_recalloc(persistent->bitmapCacheBitmapData, persistent->bitmapCacheBitmapDataSize, 1, 32);

    if (!buffer)
    {
     status = -1;
    }
    else
    {
     persistent->bitmapCacheBitmapData = buffer;
    }
   }

   entry->data = persistent->bitmapCacheBitmapData;

   if (fread(entry->data, entry->size, 1, persistent->cacheFile) != 1)
   {
    status = -1;
   }
   else
   {
    status = 1;
   }
  }
 }

 return status;
}