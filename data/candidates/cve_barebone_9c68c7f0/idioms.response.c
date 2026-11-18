void WritePixels(struct ngiflib_img *img, struct ngiflib_decode_context *context, unsigned char *pixels, unsigned short n)
{
  struct ngiflib_gif *parent = img->parent;
  int i;
  while (n > 0)
  {
    int Xtogo = (context->Xtogo < n)?context->Xtogo:n;
    if (img->gce.disposal == 0)
    {
      if (parent->mode & 1)
      {
        for (i = Xtogo; i > 0; i--)
        {
          context->frbuff_p.p8[0] = pixels[0];
          pixels++;
          context->frbuff_p.p8++;
        }
      }
      else
      {
        for (i = Xtogo; i > 0; i--)
        {
          context->frbuff_p.p32[0] = ngiflib_getpixel(img->palette, pixels[0]);
          pixels++;
          context->frbuff_p.p32++;
        }
      }
    }
    else
    {
      if (parent->mode & 1)
      {
        for (i = Xtogo; i > 0; i--)
        {
          if (pixels[0] != img->gce.transparent_color)
          {
            context->frbuff_p.p8[0] = pixels[0];
          }
          pixels++;
          context->frbuff_p.p8++;
        }
      }
      else
      {
        for (i = Xtogo; i > 0; i--)
        {
          if (pixels[0] != img->gce.transparent_color)
          {
            context->frbuff_p.p32[0] = ngiflib_getpixel(img->palette, pixels[0]);
          }
          pixels++;
          context->frbuff_p.p32++;
        }
      }
    }
    context->Xtogo -= Xtogo;
    if (context->Xtogo == 0)
    {
      context->Xtogo = img->width;
      switch (context->pass)
      {
        case 0:
          context->curY++;
          break;
        case 1:
          context->curY += 8;
          if (context->curY >= parent->height)
          {
            context->pass++;
            context->curY = img->posY + 4;
          }
          break;
        case 2:
          context->curY += 8;
          if (context->curY >= parent->height)
          {
            context->pass++;
            context->curY = img->posY + 2;
          }
          break;
        case 3:
          context->curY += 4;
          if (context->curY >= parent->height)
          {
            context->pass++;
            context->curY = img->posY + 1;
          }
          break;
        case 4:
          context->curY += 2;
          break;
      }
      if (parent->mode & 1)
      {
        context->frbuff_p.p8 = &parent->frbuff.p8[context->curY * parent->width];
      }
      else
      {
        context->frbuff_p.p8 = &parent->frbuff.p8[context->curY * parent->width * 4];
      }
      context->frbuff_p.p8 += img->posX;
    }
    n -= Xtogo;
  }
}