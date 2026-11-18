void WritePixels(ngiflib_img *i,ngiflib_decode_context *context,u8 *pixels,u16 n)

{
  ngiflib_gif *pnVar1;
  u32 *puVar2;
  ushort uVar3;
  u32 uVar4;
  uint local_3c;
  int j_1;
  int j;
  ngiflib_gif *p;
  u16 tocopy;
  u16 n_local;
  u8 *pixels_local;
  ngiflib_decode_context *context_local;
  ngiflib_img *i_local;
  
  pnVar1 = i->parent;
  pixels_local = pixels;
  for (n_local = n; n_local != 0; n_local = n_local - uVar3) {
    uVar3 = n_local;
    if (context->Xtogo < n_local) {
      uVar3 = context->Xtogo;
    }
    local_3c = (uint)uVar3;
    if ((i->gce).transparent_flag == 0) {
      if ((pnVar1->mode & 1) == 0) {
        for (j = local_3c; 0 < j; j = j + -1) {
          uVar4 = GifIndexToTrueColor(i->palette,*pixels_local);
          puVar2 = (context->frbuff_p).p32;
          (context->frbuff_p).p32 = puVar2 + 1;
          *puVar2 = uVar4;
          pixels_local = pixels_local + 1;
        }
      }
      else {
        memcpy((context->frbuff_p).p8,pixels_local,(ulong)uVar3);
        pixels_local = pixels_local + (int)local_3c;
        (context->frbuff_p).p8 = (context->frbuff_p).p8 + (int)local_3c;
      }
    }
    else if ((pnVar1->mode & 1) == 0) {
      for (j_1 = local_3c; 0 < j_1; j_1 = j_1 + -1) {
        if (*pixels_local != (i->gce).transparent_color) {
          uVar4 = GifIndexToTrueColor(i->palette,*pixels_local);
          *(context->frbuff_p).p32 = uVar4;
        }
        pixels_local = pixels_local + 1;
        (context->frbuff_p).p8 = (context->frbuff_p).p8 + 4;
      }
    }
    else {
      for (j_1 = local_3c; 0 < j_1; j_1 = j_1 + -1) {
        if (*pixels_local != (i->gce).transparent_color) {
          *(context->frbuff_p).p8 = *pixels_local;
        }
        pixels_local = pixels_local + 1;
        (context->frbuff_p).p8 = (context->frbuff_p).p8 + 1;
      }
    }
    context->Xtogo = context->Xtogo - uVar3;
    if (context->Xtogo == 0) {
      context->Xtogo = i->width;
      switch(context->pass) {
      case '\0':
        context->curY = context->curY + 1;
        break;
      case '\x01':
        context->curY = context->curY + 8;
        if (pnVar1->height <= context->curY) {
          context->pass = context->pass + '\x01';
          context->curY = i->posY + 4;
        }
        break;
      case '\x02':
        context->curY = context->curY + 8;
        if (pnVar1->height <= context->curY) {
          context->pass = context->pass + '\x01';
          context->curY = i->posY + 2;
        }
        break;
      case '\x03':
        context->curY = context->curY + 4;
        if (pnVar1->height <= context->curY) {
          context->pass = context->pass + '\x01';
          context->curY = i->posY + 1;
        }
        break;
      case '\x04':
        context->curY = context->curY + 2;
      }
      if ((pnVar1->mode & 1) == 0) {
        (context->frbuff_p).p8 =
             (pnVar1->frbuff).p8 +
             (long)(int)(uint)i->posX * 4 + (ulong)((uint)context->curY * (uint)pnVar1->width) * 4;
      }
      else {
        (context->frbuff_p).p8 =
             (pnVar1->frbuff).p8 +
             (long)(int)(uint)i->posX + (ulong)((uint)context->curY * (uint)pnVar1->width);
      }
    }
  }
  return;
}