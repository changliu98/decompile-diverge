static int persistent_cache_read_entry_v3(rdpPersistentCache * persistent, PERSISTENT_CACHE_ENTRY_V3 * entry)
{
 PERSISTENT_CACHE_ENTRY_V3 header;
 size_t size;
 int rv;

 memset(&header, 0, sizeof(header));
 do { if (!(persistent)) ___assert_fail("persistent", "harness.c", 279, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY_V3 *)"); } while (0);
 do { if (!(entry)) ___assert_fail("entry", "harness.c", 280, "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY_V3 *)"); } while (0);

 if (fread(&header, sizeof(header), 1, persistent->cache) != 1)
 {
  rv = -1;
 }
 else
 {
  entry->key64 = header.key64;
  entry->width = header.width;
  entry->height = header.height;

  size = ((unsigned int) entry->width) * 4 * ((unsigned int) entry->height);

  if (size > ((size_t)(-1)))
  {
   rv = -1;
  }
  else
  {
   entry->data_size = 0;

   if (size > persistent->max_size)
   {
    persistent->max_size = size;

    char * tmp = _ZN4chip9ArgParser11HelpOptionsC2EPKcS3_S3_(persistent->data, persistent->max_size, 1, 32);
    if (!tmp)
    {
     rv = -1;
    }
    else
    {
     persistent->data = tmp;
    }
   }

   entry->size = (unsigned int) size;
   entry->data = persistent->data;

   if (fread(entry->data, entry->size, 1, persistent->cache) != 1)
   {
    rv = -1;
   }
   else
   {
    rv = 1;
   }
  }
 }

 return rv;
}