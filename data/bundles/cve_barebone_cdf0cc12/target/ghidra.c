BITMAP_UPDATE * update_read_bitmap_update(rdpUpdate *update,wStream *s)

{
  uint uVar1;
  BOOL BVar2;
  size_t sVar3;
  BITMAP_DATA *pBVar4;
  BITMAP_DATA *newdata;
  UINT16 count;
  BITMAP_UPDATE *bitmapUpdate;
  UINT32 i;
  wStream *s_local;
  rdpUpdate *update_local;
  BITMAP_UPDATE *local_10;
  
  local_10 = calloc(1,0x18);
  if ((local_10 == (BITMAP_UPDATE *)0x0) || (sVar3 = Stream_GetRemainingLength(s), sVar3 < 2)) {
LAB_0010143a:
    free_bitmap_update(update->context,local_10);
    local_10 = (BITMAP_UPDATE *)0x0;
  }
  else {
    local_10->number = (uint)*s->pointer + (uint)s->pointer[1] * 0x100;
    Stream_Seek(s,2);
    if (local_10->count < local_10->number) {
      uVar1 = local_10->number << 1;
      pBVar4 = realloc(local_10->rectangles,(ulong)(ushort)uVar1 * 0x48);
      if (pBVar4 == (BITMAP_DATA *)0x0) goto LAB_0010143a;
      local_10->rectangles = pBVar4;
      memset(local_10->rectangles + local_10->count,0,
             (ulong)((uVar1 & 0xffff) - local_10->count) * 0x48);
      local_10->count = uVar1 & 0xffff;
    }
    for (i = 0; i < local_10->number; i = i + 1) {
      BVar2 = update_read_bitmap_data(update,s,local_10->rectangles + i);
      if (BVar2 == 0) goto LAB_0010143a;
    }
  }
  return local_10;
}