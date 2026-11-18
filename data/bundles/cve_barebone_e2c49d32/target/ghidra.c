int _gd2GetHeader(gdIOCtxPtr in,int *sx,int *sy,int *cs,int *vers,int *fmt,int *ncx,int *ncy,
                 t_chunk_info **chunkIdx)

{
  int iVar1;
  int iVar2;
  t_chunk_info *ptr;
  int nc;
  int sidx;
  t_chunk_info *cidx;
  char id [5];
  int ch;
  int i;
  int *fmt_local;
  int *vers_local;
  int *cs_local;
  int *sy_local;
  int *sx_local;
  gdIOCtxPtr in_local;
  int local_c;
  
  for (i = 0; i < 4; i = i + 1) {
    iVar1 = gdGetC(in);
    if (iVar1 == -1) goto LAB_00101c4d;
    id[i] = (char)iVar1;
  }
  id[4] = '\0';
  iVar1 = strcmp(id,"gd2");
  if (((((((iVar1 == 0) && (iVar1 = gdGetWord(vers,in), iVar1 == 1)) &&
         ((*vers == 1 || (*vers == 2)))) &&
        (((iVar1 = gdGetWord(sx,in), iVar1 != 0 && (iVar1 = gdGetWord(sy,in), iVar1 != 0)) &&
         (iVar1 = gdGetWord(cs,in), iVar1 == 1)))) && ((0x3f < *cs && (*cs < 0x1001)))) &&
      ((iVar1 = gdGetWord(fmt,in), iVar1 == 1 &&
       (((*fmt == 1 || (*fmt == 2)) || ((*fmt == 3 || (*fmt == 4)))))))) &&
     ((iVar1 = gdGetWord(ncx,in), iVar1 == 1 && (iVar1 = gdGetWord(ncy,in), iVar1 == 1)))) {
    if ((*fmt == 2) || (*fmt == 4)) {
      iVar1 = *ncx * *ncy;
      iVar2 = overflow2(8,iVar1);
      if (((iVar2 != 0) || (iVar1 * 8 < 1)) ||
         (ptr = gdCalloc((long)(iVar1 * 8),1), ptr == (t_chunk_info *)0x0)) goto LAB_00101c4d;
      for (i = 0; i < iVar1; i = i + 1) {
        iVar2 = gdGetInt(&ptr[i].offset,in);
        if (((iVar2 != 1) || (iVar2 = gdGetInt(&ptr[i].size,in), iVar2 != 1)) ||
           ((ptr[i].offset < 0 || (ptr[i].size < 0)))) {
          gdFree(ptr);
          goto LAB_00101c4d;
        }
      }
      *chunkIdx = ptr;
    }
    local_c = 1;
  }
  else {
LAB_00101c4d:
    local_c = 0;
  }
  return local_c;
}