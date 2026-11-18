void __cdecl WritePixels(ngiflib_img *i, ngiflib_decode_context *context, const u8 *pixels, u16 n)
{
  ngiflib_gif *p = i->parent;
  u16 Xtogo;
  int j;

  while (n)
  {
    // Determine how many pixels to process in this chunk
    Xtogo = (context->Xtogo >= (int)n) ? n : context->Xtogo;

    // Check if transparency is enabled (assuming gce is a struct where the 4th byte holds flags)
    bool has_transparency = (*((u8 *)&i->gce + 3) & 0x10) != 0;
    bool is_indexed_mode = (p->mode & 1) != 0;

    if (has_transparency)
    {
      if (is_indexed_mode)
      {
        for (j = Xtogo; j > 0; --j)
        {
          if (*pixels != i->gce.transparent_color)
            *context->frbuff_p.p8 = *pixels;
          ++pixels;
          ++context->frbuff_p.p8;
        }
      }
      else
      {
        for (j = Xtogo; j > 0; --j)
        {
          if (*pixels != i->gce.transparent_color)
            *context->frbuff_p.p32 = GifIndexToTrueColor(i->palette, *pixels);
          ++pixels;
          context->frbuff_p.p8 += 4;
        }
      }
    }
    else if (is_indexed_mode)
    {
      memcpy(context->frbuff_p.p8, pixels, Xtogo);
      pixels += Xtogo;
      context->frbuff_p.p8 += Xtogo;
    }
    else
    {
      for (j = Xtogo; j > 0; --j)
      {
        *context->frbuff_p.p32 = GifIndexToTrueColor(i->palette, *pixels);
        ++pixels;
        context->frbuff_p.p8 += 4;
      }
    }

    context->Xtogo -= Xtogo;
    if (!context->Xtogo)
    {
      // Reset X counter to image width and advance Y coordinate based on interlace pass
      context->Xtogo = i->width;
      switch (context->pass)
      {
        case 0u:
          ++context->curY;
          break;
        case 1u:
          context->curY += 8;
          if (context->curY >= (int)p->height)
          {
            ++context->pass;
            context->curY = i->posY + 4;
          }
          break;
        case 2u:
          context->curY += 8;
          if (context->curY >= (int)p->height)
          {
            ++context->pass;
            context->curY = i->posY + 2;
          }
          break;
        case 3u:
          context->curY += 4;
          if (context->curY >= (int)p->height)
          {
            ++context->pass;
            context->curY = i->posY + 1;
          }
          break;
        case 4u:
          context->curY += 2;
          break;
        default:
          break;
      }

      // Recalculate frame buffer pointer for the new line
      if (is_indexed_mode)
      {
        context->frbuff_p.p8 = p->frbuff.p8 + (p->width * context->curY) + i->posX;
      }
      else
      {
        context->frbuff_p.p8 = p->frbuff.p8 + (4 * p->width * context->curY) + (4 * i->posX);
      }
    }
    
    n -= Xtogo;
  }
}