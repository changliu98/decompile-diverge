void WritePixels(ngiflib_img *i, ngiflib_decode_context *context, unsigned char *pixels, unsigned short n)
{
    ngiflib_gif *gif = i->parent;
    while (n) {
        unsigned short tocopy = n > context->Xtogo ? context->Xtogo : n;
        if (!i->gce.transparent_flag) {
            if (gif->mode & 0x01) {
                memcpy(context->frbuff_p.p8, pixels, tocopy);
                pixels += tocopy;
                context->frbuff_p.p8 += tocopy;
            } else {
                int j = tocopy;
                while (j-- > 0) {
                    *(context->frbuff_p.p32++) = GifIndexToTrueColor(i->palette, *pixels++);
                }
            }
        } else {
            if (gif->mode & 0x01) {
                int j = tocopy;
                while (j-- > 0) {
                    if (*pixels != i->gce.transparent_color) {
                        *(context->frbuff_p.p8) = *pixels;
                    }
                    pixels++;
                    context->frbuff_p.p8++;
                }
            } else {
                int j = tocopy;
                while (j-- > 0) {
                    if (*pixels != i->gce.transparent_color) {
                        *(context->frbuff_p.p32) = GifIndexToTrueColor(i->palette, *pixels);
                    }
                    pixels++;
                    context->frbuff_p.p8 += 4;
                }
            }
        }
        n -= tocopy;
        context->Xtogo -= tocopy;
        if (!context->Xtogo) {
            context->Xtogo = i->width;
            switch (context->pass) {
            case 0:
                context->curY++;
                break;
            case 1:
                context->curY += 8;
                if (context->curY >= gif->height) {
                    context->pass++;
                    context->curY = i->posY + 4;
                }
                break;
            case 2:
                context->curY += 8;
                if (context->curY >= gif->height) {
                    context->pass++;
                    context->curY = i->posY + 2;
                }
                break;
            case 3:
                context->curY += 4;
                if (context->curY >= gif->height) {
                    context->pass++;
                    context->curY = i->posY + 1;
                }
                break;
            case 4:
                context->curY += 2;
                break;
            }
            if (gif->mode & 0x01) {
                context->frbuff_p.p8 = gif->frbuff.p8 + i->posX + context->curY * gif->width;
            } else {
                context->frbuff_p.p8 = gif->frbuff.p8 + i->posX * 4 + context->curY * gif->width * 4;
            }
        }
    }
}