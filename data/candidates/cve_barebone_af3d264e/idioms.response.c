struct _gdImage *gdImageCreateFromTgaCtx(struct gdIOCtx *io)
{
  int i; int j; int k;
  struct _gdImage *image;
  struct oTga *tga;
  unsigned int *tpix;
  i = 0;
  tga = (struct oTga *)gdImageAlloc(sizeof(oTga));
  if (tga == ((void *)0))
    return ((void *)0);
  tga->bitmap = ((void *)0);
  tga->ident = ((void *)0);
  if (readHeader(io, tga) < 0 || readBitmap(io, tga) < 0)
  {
    freeTga(tga);
    return ((void *)0);
  }
  image = gdImageCreateTrueColor(tga->width, tga->height);
  if (image == ((void *)0))
  {
    freeTga(tga);
    return ((void *)0);
  }
  if (tga->alphabits)
  {
    gdImageColorTransparent(image, 0);
    gdImageColorTransparent(image, 1);
  }
  for (j = 0; j < tga->height; j++)
  {
    tpix = image->tpixels[j];
    for (i = 0; i < tga->width; i++)
    {
      if (tga->bits == 24)
      {
        tpix[i] = tga->bitmap[i * 3 + k]
          + (tga->bitmap[i * 3 + 1 + k] << 8)
          + (tga->bitmap[i * 3 + 2 + k] << 16);
        k += 3;
      }
      else if (tga->bits == 32 || tga->alphabits)
      {
        tpix[i] = tga->bitmap[i * 4 + k]
          + (tga->bitmap[i * 4 + 1 + k] << 8)
          + (tga->bitmap[i * 4 + 2 + k] << 16)
          + (tga->bitmap[i * 4 + 3 + k] << 24);
        k += 4;
      }
      tpix++;
    }
  }
  if (tga->flipv && tga->fliph)
    gdImageFlip(image);
  else if (tga->flipv)
    gdImageFlipV(image);
  else if (tga->fliph)
    gdImageFlipH(image);
  freeTga(tga);
  return image;
}