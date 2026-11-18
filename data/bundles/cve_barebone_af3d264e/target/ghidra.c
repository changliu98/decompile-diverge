gdImagePtr gdImageCreateFromTgaCtx(gdIOCtx *ctx)

{
  int iVar1;
  oTga *tga_00;
  int a;
  int *tpix;
  int y;
  int x;
  gdImagePtr image;
  oTga *tga;
  int bitmap_caret;
  gdIOCtx *ctx_local;
  gdImagePtr local_10;
  
  bitmap_caret = 0;
  tga_00 = gdMalloc(0x38);
  if (tga_00 == (oTga *)0x0) {
    local_10 = (gdImagePtr)0x0;
  }
  else {
    tga_00->bitmap = (int *)0x0;
    tga_00->ident = (char *)0x0;
    iVar1 = read_header_tga(ctx,tga_00);
    if (iVar1 < 0) {
      free_tga(tga_00);
      local_10 = (gdImagePtr)0x0;
    }
    else {
      iVar1 = read_image_tga(ctx,tga_00);
      if (iVar1 < 0) {
        free_tga(tga_00);
        local_10 = (gdImagePtr)0x0;
      }
      else {
        local_10 = gdImageCreateTrueColor(tga_00->width,tga_00->height);
        if (local_10 == (gdImagePtr)0x0) {
          free_tga(tga_00);
          local_10 = (gdImagePtr)0x0;
        }
        else {
          if (tga_00->alphabits != '\0') {
            gdImageAlphaBlending(local_10,0);
            gdImageSaveAlpha(local_10,1);
          }
          for (y = 0; y < tga_00->height; y = y + 1) {
            tpix = local_10->tpixels[y];
            for (x = 0; x < tga_00->width; x = x + 1) {
              if (tga_00->bits == '\x18') {
                *tpix = tga_00->bitmap[bitmap_caret + 2] * 0x10000 +
                        tga_00->bitmap[bitmap_caret + 1] * 0x100 + tga_00->bitmap[bitmap_caret];
                bitmap_caret = bitmap_caret + 3;
              }
              else if ((tga_00->bits == ' ') || (tga_00->alphabits != '\0')) {
                *tpix = (0x7f - (tga_00->bitmap[bitmap_caret + 3] >> 1)) * 0x1000000 +
                        tga_00->bitmap[bitmap_caret + 2] * 0x10000 +
                        tga_00->bitmap[bitmap_caret + 1] * 0x100 + tga_00->bitmap[bitmap_caret];
                bitmap_caret = bitmap_caret + 4;
              }
              tpix = tpix + 1;
            }
          }
          if ((tga_00->flipv == '\0') || (tga_00->fliph == '\0')) {
            if (tga_00->flipv == '\0') {
              if (tga_00->fliph != '\0') {
                gdImageFlipHorizontal(local_10);
              }
            }
            else {
              gdImageFlipVertical(local_10);
            }
          }
          else {
            gdImageFlipBoth(local_10);
          }
          free_tga(tga_00);
        }
      }
    }
  }
  return local_10;
}