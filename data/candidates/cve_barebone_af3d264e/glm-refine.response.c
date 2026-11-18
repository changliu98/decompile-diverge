gdImagePtr __cdecl gdImageCreateFromTgaCtx(gdIOCtx *ctx)
{
  oTga *tga;
  gdImagePtr image;
  int bitmap_caret;
  int x, y;
  int *tpix;

  bitmap_caret = 0;
  tga = (oTga *)gdMalloc(0x38uLL);
  if (!tga)
    return NULL;

  tga->bitmap = NULL;
  tga->ident = NULL;

  if (read_header_tga(ctx, tga) < 0 || read_image_tga(ctx, tga) < 0)
    goto fail;

  image = gdImageCreateTrueColor(tga->width, tga->height);
  if (!image)
    goto fail;

  if (tga->alphabits)
  {
    gdImageAlphaBlending(image, 0);
    gdImageSaveAlpha(image, 1);
  }

  for (y = 0; y < tga->height; ++y)
  {
    tpix = image->tpixels[y];
    for (x = 0; x < tga->width; ++x)
    {
      if (tga->bits == 24)
      {
        *tpix = tga->bitmap[bitmap_caret]
              | (tga->bitmap[bitmap_caret + 1] << 8)
              | (tga->bitmap[bitmap_caret + 2] << 16);
        bitmap_caret += 3;
      }
      else if (tga->bits == 32 || tga->alphabits)
      {
        *tpix = tga->bitmap[bitmap_caret]
              | (tga->bitmap[bitmap_caret + 1] << 8)
              | (tga->bitmap[bitmap_caret + 2] << 16)
              | ((127 - (tga->bitmap[bitmap_caret + 3] >> 1)) << 24);
        bitmap_caret += 4;
      }
      ++tpix;
    }
  }

  if (tga->flipv && tga->fliph)
  {
    aes_ctx_free(image);
  }
  else if (tga->flipv)
  {
    gdImageFlipVertical(image);
  }
  else if (tga->fliph)
  {
    gdImageFlipHorizontal(image);
  }

  free_tga(tga);
  return image;

fail:
  free_tga(tga);
  return NULL;
}