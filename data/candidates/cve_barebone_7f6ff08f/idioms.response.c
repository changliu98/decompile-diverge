void WritePixels(struct ngiflib_img *img, struct ngiflib_decode_context *context, unsigned char *line, int n)
{
  struct ngiflib_gif *gif = img->parent;
  int i;
  int Xtogo;
  if (n > 0) {
    if (context->Xtogo < n)
      Xtogo = context->Xtogo;
    else
      Xtogo = n;
    if (img->gce.use_transparent) {
      if (gif->mode & 1) {
        for (i = Xtogo; i > 0; i--) {
          if (line[0] != img->gce.transparent_color)
            ((context->frbuff_p).p8)[0] = line[0];
          line++;
          ((context->frbuff_p).p8)++;
        }
      } else {
        for (i = Xtogo; i > 0; i--) {
          if (line[0] != img->gce.transparent_color)
            ((context->frbuff_p).p32)[0] = ngiflib_get_color(img->palette, line[0]);
          line++;
          ((context->frbuff_p).p32)++;
        }
      }
    } else {
      if (gif->mode & 1) {
        ngiflib_decode_line_raw(context->frbuff_p.p8, line, Xtogo);
        line += Xtogo;
        context->frbuff_p.p8 += Xtogo;
      } else {
        for (i = Xtogo; i > 0; i--) {
          ((context->frbuff_p).p32)[0] = ngiflib_get_color(img->palette, line[0]);
          line++;
          ((context->frbuff_p).p32)++;
        }
      }
    }
    context->Xtogo -= Xtogo;
    if (context->Xtogo == 0) {
      context->Xtogo = img->width;
      switch (context->pass) {
        case 0:
          context->curY++;
          break;
        case 1:
          context->curY += 8;
          if (context->curY >= gif->height) {
            context->pass++;
            context->curY = img->posY + 4;
          }
          break;
        case 2:
          context->curY += 8;
          if (context->curY >= gif->height) {
            context->pass++;
            context->curY = img->posY + 2;
          }
          break;
        case 3:
          context->curY += 4;
          if (context->curY >= gif->height) {
            context->pass++;
            context->curY = img->posY + 1;
          }
          break;
        case 4:
          context->curY += 2;
          break;
      }
      if (gif->mode & 1)
        context->frbuff_p.p8 = &gif->frbuff.p8[context->curY * gif->width + img->posX];
      else
        context->frbuff_p.p8 = &gif->frbuff.p8[context->curY * (gif->width * 4) + (img->posX * 4)];
    }
    n -= Xtogo;
  }
}