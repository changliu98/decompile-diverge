void process_bitmap_updates(STREAM s)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  ushort uVar9;
  ushort uVar10;
  ushort uVar11;
  RD_BOOL RVar12;
  uint8 *puVar13;
  uint8 *output;
  uint8 *in_stack_ffffffffffffff78;
  int y;
  int i;
  uint8 *bmpdata;
  uint8 *data;
  uint16 size;
  uint16 bufsize;
  uint16 compress;
  uint16 Bpp;
  uint16 bpp;
  uint16 cy;
  uint16 cx;
  uint16 height;
  uint16 width;
  uint16 bottom;
  uint16 right;
  uint16 top;
  uint16 left;
  uint16 num_updates;
  STREAM s_local;
  
  logger(Protocol,Debug,"%s()","process_bitmap_updates");
  uVar1 = *(ushort *)s->p;
  s->p = s->p + 2;
  for (i = 0; i < (int)(uint)uVar1; i = i + 1) {
    uVar2 = *(ushort *)s->p;
    s->p = s->p + 2;
    uVar3 = *(ushort *)s->p;
    s->p = s->p + 2;
    uVar4 = *(ushort *)s->p;
    s->p = s->p + 2;
    uVar5 = *(ushort *)s->p;
    s->p = s->p + 2;
    uVar6 = *(ushort *)s->p;
    s->p = s->p + 2;
    uVar7 = *(ushort *)s->p;
    s->p = s->p + 2;
    uVar8 = *(ushort *)s->p;
    s->p = s->p + 2;
    uVar9 = (ushort)((ulong)(uVar8 + 7) / 8);
    uVar8 = *(ushort *)s->p;
    s->p = s->p + 2;
    size = *(uint16 *)s->p;
    s->p = s->p + 2;
    uVar10 = (uVar4 - uVar2) + 1;
    uVar11 = (uVar5 - uVar3) + 1;
    in_stack_ffffffffffffff78 =
         (uint8 *)CONCAT44((int)((ulong)in_stack_ffffffffffffff78 >> 0x20),(uint)uVar5);
    logger(Graphics,Debug,"process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d"
           ,(ulong)uVar2,(ulong)uVar3,(ulong)uVar4,in_stack_ffffffffffffff78,(uint)uVar6,(uint)uVar7
           ,(uint)uVar9,(uint)uVar8);
    if (uVar8 == 0) {
      puVar13 = xmalloc((uint)uVar6 * (uint)uVar7 * (uint)uVar9);
      for (y = 0; y < (int)(uint)uVar7; y = y + 1) {
        memcpy(puVar13 + (int)((((uint)uVar7 - y) + -1) * (uint)uVar6 * (uint)uVar9),s->p,
               (long)(int)((uint)uVar6 * (uint)uVar9));
        s->p = s->p + (int)((uint)uVar6 * (uint)uVar9);
      }
      in_stack_ffffffffffffff78 = puVar13;
      ui_paint_bitmap((uint)uVar2,(uint)uVar3,(uint)uVar10,(uint)uVar11,(uint)uVar6,(uint)uVar7,
                      puVar13);
      xfree(puVar13);
    }
    else {
      if ((uVar8 & 0x400) == 0) {
        s->p = s->p + 2;
        size = *(uint16 *)s->p;
        s->p = s->p + 2;
        s->p = s->p + 4;
      }
      puVar13 = s->p;
      s->p = s->p + (int)(uint)size;
      output = xmalloc((uint)uVar6 * (uint)uVar7 * (uint)uVar9);
      RVar12 = bitmap_decompress(output,(uint)uVar6,(uint)uVar7,puVar13,(uint)size,(uint)uVar9);
      if (RVar12 == 0) {
        logger(Graphics,Warning,"process_bitmap_updates(), failed to decompress bitmap");
      }
      else {
        in_stack_ffffffffffffff78 = output;
        ui_paint_bitmap((uint)uVar2,(uint)uVar3,(uint)uVar10,(uint)uVar11,(uint)uVar6,(uint)uVar7,
                        output);
      }
      xfree(output);
    }
  }
  return;
}