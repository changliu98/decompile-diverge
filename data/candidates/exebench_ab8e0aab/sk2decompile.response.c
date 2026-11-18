void crc32_final(unsigned int *crc) {
  *crc = ~*crc;
  *crc &= 0xffffffffL;
# 106 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/GeeXboX/mplayer-ui/refs/heads/master/libmpdvdkit2/crc32.c"
}