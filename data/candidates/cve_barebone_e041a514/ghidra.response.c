int _gd2GetHeader(gdIOCtxPtr in,int *sx,int *sy,int *cs,int *vers,int *fmt,int *ncx,int *ncy,
                 t_chunk_info **chunkIdx)

{
  int iVar1;
  int iVar2;
  int iVar3;
  t_chunk_info *__ptr;
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
    iVar2 = gdGetC(in);
    if (iVar2 == -1) goto LAB_00101b44;
    id[i] = (char)iVar2;
  }
  id[4] = '\0';
  iVar2 = strcmp(id,"gd2");
  if (((((iVar2 == 0) && (iVar2 = gdGetWord(vers,in), iVar2 == 1)) && ((*vers == 1 || (*vers == 2)))
       ) && (((((iVar2 = gdGetWord(sx,in), iVar2 != 0 && (iVar2 = gdGetWord(sy,in), iVar2 != 0)) &&
               (iVar2 = gdGetWord(cs,in), iVar2 == 1)) && ((0x3f < *cs && (*cs < 0x1001)))) &&
             (iVar2 = gdGetWord(fmt,in), iVar2 == 1)))) &&
     ((((*fmt == 1 || (*fmt == 2)) || ((*fmt == 3 || (*fmt == 4)))) &&
      ((iVar2 = gdGetWord(ncx,in), iVar2 == 1 && (iVar2 = gdGetWord(ncy,in), iVar2 == 1)))))) {
    if ((*fmt == 2) || (*fmt == 4)) {
      iVar2 = *ncx;
      iVar1 = *ncy;
      iVar3 = iVar2 * iVar1 * 8;
      if (iVar3 < 1) goto LAB_00101b44;
      __ptr = calloc((long)iVar3,1);
      for (i = 0; i < iVar2 * iVar1; i = i + 1) {
        iVar3 = gdGetInt(&__ptr[i].offset,in);
        if (iVar3 != 1) {
          free(__ptr);
          goto LAB_00101b44;
        }
        iVar3 = gdGetInt(&__ptr[i].size,in);
        if (iVar3 != 1) {
          free(__ptr);
          goto LAB_00101b44;
        }
        if ((__ptr[i].offset < 0) || (__ptr[i].size < 0)) {
          free(__ptr);
          goto LAB_00101b44;
        }
      }
      *chunkIdx = __ptr;
    }
    local_c = 1;
  }
  else {
LAB_00101b44:
    local_c = 0;
  }
  return local_c;
}