void __cdecl WritePixels(ngiflib_img *i, ngiflib_decode_context *context, const u8 *pixels, u16 n)
{
  u8 *v4; // rax
  u32 v5; // ecx
  u32 *p8; // rax
  __int64 v7; // rcx
  __int64 posX; // rax
  u16 Xtogo; // [rsp+Ch] [rbp-34h]
  int j_0; // [rsp+10h] [rbp-30h]
  int j_0a; // [rsp+10h] [rbp-30h]
  int j; // [rsp+14h] [rbp-2Ch]
  ngiflib_gif *p; // [rsp+18h] [rbp-28h]

  p = i->parent;
  while ( n )
  {
    if ( context->Xtogo >= (int)n )
      Xtogo = n;
    else
      Xtogo = context->Xtogo;
    if ( (*((_BYTE *)&i->gce + 3) & 0x10) != 0 )
    {
      if ( (p->mode & 1) != 0 )
      {
        for ( j_0 = Xtogo; j_0 > 0; --j_0 )
        {
          if ( *pixels != i->gce.transparent_color )
            *context->frbuff_p.p8 = *pixels;
          ++pixels;
          ++context->frbuff_p.p8;
        }
      }
      else
      {
        for ( j_0a = Xtogo; j_0a > 0; --j_0a )
        {
          if ( *pixels != i->gce.transparent_color )
            *context->frbuff_p.p32 = GifIndexToTrueColor(i->palette, *pixels);
          ++pixels;
          context->frbuff_p.p8 += 4;
        }
      }
    }
    else if ( (p->mode & 1) != 0 )
    {
      memcpy(context->frbuff_p.p8, pixels, Xtogo);
      pixels += Xtogo;
      context->frbuff_p.p8 += Xtogo;
    }
    else
    {
      for ( j = Xtogo; j > 0; --j )
      {
        v4 = (u8 *)pixels++;
        v5 = GifIndexToTrueColor(i->palette, *v4);
        p8 = (u32 *)context->frbuff_p.p8;
        context->frbuff_p.p8 += 4;
        *p8 = v5;
      }
    }
    context->Xtogo -= Xtogo;
    if ( !context->Xtogo )
    {
      context->Xtogo = i->width;
      switch ( context->pass )
      {
        case 0u:
          ++context->curY;
          break;
        case 1u:
          context->curY += 8;
          if ( context->curY >= (int)p->height )
          {
            ++context->pass;
            context->curY = i->posY + 4;
          }
          break;
        case 2u:
          context->curY += 8;
          if ( context->curY >= (int)p->height )
          {
            ++context->pass;
            context->curY = i->posY + 2;
          }
          break;
        case 3u:
          context->curY += 4;
          if ( context->curY >= (int)p->height )
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
      if ( (p->mode & 1) != 0 )
      {
        v7 = (__int64)&p->frbuff.p8[p->width * context->curY];
        posX = i->posX;
      }
      else
      {
        v7 = (__int64)&p->frbuff.p8[4 * p->width * context->curY];
        posX = 4LL * i->posX;
      }
      context->frbuff_p.p8 = (u8 *)(posX + v7);
    }
    n -= Xtogo;
  }
}