int __cdecl persistent_cache_read_entry_v3(rdpPersistentCache *persistent, PERSISTENT_CACHE_ENTRY *entry)
{
  BYTE *bmpData; // [rsp+8h] [rbp-38h]
  UINT64 size; // [rsp+10h] [rbp-30h]
  PERSISTENT_CACHE_ENTRY_V3 entry3; // [rsp+18h] [rbp-28h] BYREF
  PERSISTENT_CACHE_ENTRY *entrya; // [rsp+28h] [rbp-18h]
  rdpPersistentCache *persistenta; // [rsp+30h] [rbp-10h]

  persistenta = persistent;
  entrya = entry;
  memset(&entry3, 0, sizeof(entry3));
  if ( !persistenta )
    __assert_fail(
      "persistent",
      "/work/harness.c",
      0x117u,
      "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)");
  if ( !entrya )
    __assert_fail(
      "entry",
      "/work/harness.c",
      0x118u,
      "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)");
  if ( fread(&entry3, 0xCuLL, 1uLL, persistenta->fp) != 1 )
    return -1;
  entrya->key64 = entry3.key64;
  entrya->width = entry3.width;
  entrya->height = entry3.height;
  size = entry3.height * 4LL * entry3.width;
  if ( size > 0xFFFFFFFF )
    return -1;
  entrya->flags = 0;
  if ( size > persistenta->bmpSize )
  {
    persistenta->bmpSize = size;
    bmpData = (BYTE *)chip::ArgParser::HelpOptions::HelpOptions(
                        persistenta->bmpData,
                        persistenta->bmpSize,
                        1uLL,
                        0x20uLL);
    if ( !bmpData )
      return -1;
    persistenta->bmpData = bmpData;
  }
  entrya->size = size;
  entrya->data = persistenta->bmpData;
  if ( fread(entrya->data, entrya->size, 1uLL, persistenta->fp) == 1 )
    return 1;
  else
    return -1;
}