int persistent_cache_read_entry_v3(rdpPersistentCache *persistent,PERSISTENT_CACHE_ENTRY *entry)

{
  size_t sVar1;
  ulong uVar2;
  BYTE *pBVar3;
  BYTE *bmpData;
  UINT64 size;
  PERSISTENT_CACHE_ENTRY_V3 entry3;
  PERSISTENT_CACHE_ENTRY *entry_local;
  rdpPersistentCache *persistent_local;
  int local_c;
  
  memset(&entry3,0,0xc);
  if (persistent == (rdpPersistentCache *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("persistent","/work/harness.c",0x71,
                  "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)"
                 );
  }
  if (entry != (PERSISTENT_CACHE_ENTRY *)0x0) {
    sVar1 = fread(&entry3,0xc,1,(FILE *)persistent->fp);
    if (sVar1 == 1) {
      entry->key64 = entry3.key64;
      entry->width = entry3.width;
      entry->height = entry3.height;
      uVar2 = (ulong)entry3.width * 4 * (ulong)entry3.height;
      if (uVar2 < 0x100000000) {
        entry->size = (UINT32)uVar2;
        entry->flags = 0;
        if (persistent->bmpSize < entry->size) {
          persistent->bmpSize = entry->size;
          pBVar3 = winpr_aligned_recalloc(persistent->bmpData,(ulong)persistent->bmpSize,1,0x20);
          if (pBVar3 == (BYTE *)0x0) {
            return -1;
          }
          persistent->bmpData = pBVar3;
        }
        entry->data = persistent->bmpData;
        sVar1 = fread(entry->data,(ulong)entry->size,1,(FILE *)persistent->fp);
        if (sVar1 == 1) {
          local_c = 1;
        }
        else {
          local_c = -1;
        }
      }
      else {
        local_c = -1;
      }
    }
    else {
      local_c = -1;
    }
    return local_c;
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("entry","/work/harness.c",0x72,
                "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)"
               );
}