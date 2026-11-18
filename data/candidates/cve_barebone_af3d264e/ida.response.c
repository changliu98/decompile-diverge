gdImagePtr __cdecl gdImageCreateFromTgaCtx(gdIOCtx *ctx)
{
  int *tpix; // [rsp+8h] [rbp-38h]
  int y; // [rsp+10h] [rbp-30h]
  int x; // [rsp+14h] [rbp-2Ch]
  gdImagePtr image; // [rsp+18h] [rbp-28h]
  oTga *tga; // [rsp+20h] [rbp-20h]
  int bitmap_caret; // [rsp+2Ch] [rbp-14h]

  bitmap_caret = 0;
  tga = (oTga *)gdMalloc(0x38uLL);
  if ( !tga )
    return 0LL;
  tga->bitmap = 0LL;
  tga->ident = 0LL;
  if ( read_header_tga(ctx, tga) >= 0
    && read_image_tga(ctx, tga) >= 0
    && (image = gdImageCreateTrueColor(tga->width, tga->height)) != 0LL )
  {
    if ( tga->alphabits )
    {
      gdImageAlphaBlending(image, 0);
      gdImageSaveAlpha(image, 1);
    }
    for ( y = 0; y < tga->height; ++y )
    {
      tpix = image->tpixels[y];
      for ( x = 0; x < tga->width; ++x )
      {
        if ( tga->bits == 24 )
        {
          *tpix = tga->bitmap[bitmap_caret]
                + (tga->bitmap[bitmap_caret + 1] << 8)
                + (tga->bitmap[bitmap_caret + 2] << 16);
          bitmap_caret += 3;
        }
        else if ( tga->bits == 32 || tga->alphabits )
        {
          *tpix = tga->bitmap[bitmap_caret]
                + (tga->bitmap[bitmap_caret + 1] << 8)
                + (tga->bitmap[bitmap_caret + 2] << 16)
                + ((127 - (tga->bitmap[bitmap_caret + 3] >> 1)) << 24);
          bitmap_caret += 4;
        }
        ++tpix;
      }
    }
    if ( tga->flipv && tga->fliph )
    {
      aes_ctx_free(image);
    }
    else if ( tga->flipv )
    {
      gdImageFlipVertical(image);
    }
    else if ( tga->fliph )
    {
      gdImageFlipHorizontal(image);
    }
    free_tga(tga);
    return image;
  }
  else
  {
    free_tga(tga);
    return 0LL;
  }
}