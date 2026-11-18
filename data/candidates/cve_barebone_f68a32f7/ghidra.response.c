BOOL resize_vbar_entry(CLEAR_CONTEXT *clear,CLEAR_VBAR_ENTRY *vBarEntry)

{
  UINT32 UVar1;
  UINT32 UVar2;
  UINT32 UVar3;
  UINT32 UVar4;
  BYTE *pBVar5;
  BYTE *tmp;
  UINT32 diffSize;
  UINT32 oldPos;
  UINT32 bpp;
  CLEAR_VBAR_ENTRY *vBarEntry_local;
  CLEAR_CONTEXT *clear_local;
  BOOL local_c;
  
  if (vBarEntry->size < vBarEntry->count) {
    UVar4 = FreeRDPGetBytesPerPixel(clear->format);
    UVar1 = vBarEntry->size;
    UVar2 = vBarEntry->count;
    UVar3 = vBarEntry->size;
    vBarEntry->size = vBarEntry->count;
    pBVar5 = winpr_aligned_recalloc(vBarEntry->pixels,(ulong)vBarEntry->count,(ulong)UVar4,0x20);
    if (pBVar5 == (BYTE *)0x0) {
      return 0;
    }
    memset(pBVar5 + UVar1 * UVar4,0,(ulong)((UVar2 - UVar3) * UVar4));
    vBarEntry->pixels = pBVar5;
  }
  if ((vBarEntry->pixels == (BYTE *)0x0) && (vBarEntry->size != 0)) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}