int do_bid_note(magic_set *ms,uchar *nbuf,uint32_t type,int swap,uint32_t namesz,uint32_t descsz,
               size_t noff,size_t doff,int *flags)

{
  int iVar1;
  uint32_t i;
  char *btype;
  uint8_t desc [20];
  uint32_t descsz_local;
  uint32_t namesz_local;
  int swap_local;
  uint32_t type_local;
  uchar *nbuf_local;
  magic_set *ms_local;
  
  if ((((namesz != 4) || (iVar1 = strcmp((char *)(nbuf + noff),"GNU"), iVar1 != 0)) || (type != 3))
     || ((descsz < 4 && (0x14 < descsz)))) {
    return 0;
  }
  *flags = *flags | 0x10;
  if (descsz == 8) {
    btype = "xxHash";
  }
  else if (descsz == 0x10) {
    btype = "md5/uuid";
  }
  else if (descsz == 0x14) {
    btype = "sha1";
  }
  else {
    btype = "unknown";
  }
  iVar1 = file_printf(ms,", BuildID[%s]=",btype);
  if (iVar1 == -1) {
    return 1;
  }
  memcpy(desc,nbuf + doff,(ulong)descsz);
  i = 0;
  while( true ) {
    if (descsz <= i) {
      return 1;
    }
    iVar1 = file_printf(ms,"%02x",(ulong)desc[i]);
    if (iVar1 == -1) break;
    i = i + 1;
  }
  return 1;
}