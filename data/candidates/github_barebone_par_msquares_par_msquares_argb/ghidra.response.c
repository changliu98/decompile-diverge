uint32_t par_msquares_argb(par_byte *pdata,int bpp)

{
  int j;
  uint32_t color;
  int bpp_local;
  par_byte *pdata_local;
  uint32_t local_c;
  
  color = 0;
  if (bpp == 4) {
    local_c = CONCAT13(pdata[3],CONCAT12(*pdata,CONCAT11(pdata[1],pdata[2])));
  }
  else {
    for (j = 0; j < bpp; j = j + 1) {
      color = (uint)pdata[j] | color << 8;
    }
    local_c = color;
  }
  return local_c;
}