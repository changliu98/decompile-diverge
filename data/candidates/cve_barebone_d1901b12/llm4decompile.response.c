int
do_bid_note(struct magic_set *ms, const unsigned char *buf, uint32_t type,
    int swap, uint32_t namesz, uint32_t descsz, uint32_t noff, uint32_t doff,
    int *flags)
{
 const char *btype;
 unsigned char desc[20];
 uint32_t i;

 if (namesz != 4 || strcmp((const char *)buf + noff, "GNU") != 0 ||
     type != 3)
  return 0;

 if (descsz < 4 && descsz > sizeof(desc))
  return 0;

 *flags |= 0x10;

 if (descsz == 8)
  btype = "xxHash";
 else if (descsz == 16)
  btype = "md5/uuid";
 else if (descsz == 20)
  btype = "sha1";
 else
  btype = "unknown";

 if (file_printf(ms, ", BuildID[%s]=", btype) == -1)
  return 1;

 memcpy(desc, buf + doff, descsz);
 for (i = 0; i < descsz; i++) {
  if (file_printf(ms, "%02x", desc[i]) == -1)
   return 1;
 }
 return 1;
}