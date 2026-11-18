static void
WritePixels(GifContext *Gif, GifWriter *Writer, unsigned char *Data,
            unsigned short DataLen)
{
    int i;
    unsigned char *Pal = Gif->GlobalPal;
    unsigned short Len;

    while (DataLen > 0) {
        if (DataLen > Writer->Left) {
            Len = Writer->Left;
        } else {
            Len = DataLen;
        }

        if (((Gif->Flags & 0x1000) >> 12) == 0) {
            if ((Pal[0x43] & 1) != 0) {
                memcpy(Writer->Bitmap, Data, Len);
                Data += Len;
                Writer->Bitmap += Len;
            } else {
                for (i = Len; i > 0; i--) {
                    *(Writer->Bitmap++) = GifIndexToTrueColor(Gif->GlobalPal, *Data++);
                }
            }
        } else {
            if ((Pal[0x43] & 1) != 0) {
                for (i = Len; i > 0; i--) {
                    if (*Data != Gif->Background) {
                        *Writer->Bitmap = *Data;
                    }
                    Data++;
                    Writer->Bitmap++;
                }
            } else {
                for (i = Len; i > 0; i--) {
                    if (*Data != Gif->Background) {
                        *Writer->Bitmap = GifIndexToTrueColor(Gif->GlobalPal, *Data);
                    }
                    Data++;
                    Writer->Bitmap += 4;
                }
            }
        }

        Writer->Left -= Len;
        if (Writer->Left == 0) {
            Writer->Left = Gif->ImageWidth;
            switch (Writer->Pass) {
                case 0:
                    Writer->Y += 8;
                    break;
                case 1:
                    Writer->Y += 8;
                    if (Writer->Y >= Pal[0x3C]) {
                        Writer->Pass++;
                        Writer->Y = Gif->ImageTop + 4;
                    }
                    break;
                case 2:
                    Writer->Y += 8;
                    if (Writer->Y >= Pal[0x3C]) {
                        Writer->Pass++;
                        Writer->Y = Gif->ImageTop + 2;
                    }
                    break;
                case 3:
                    Writer->Y += 4;
                    if (Writer->Y >= Pal[0x3C]) {
                        Writer->Pass++;
                        Writer->Y = Gif->ImageTop + 1;
                    }
                    break;
                case 4:
                    Writer->Y += 2;
                    break;
            }

            if ((Pal[0x43] & 1) != 0) {
                Writer->Bitmap = (unsigned char *)Pal[0x20] +
                                  (unsigned long)Writer->Y * (unsigned long)Pal[0x3A] +
                                  (unsigned long)Gif->ImageLeft;
            } else {
                Writer->Bitmap = (unsigned char *)Pal[0x20] +
                                  (unsigned long)Writer->Y * (unsigned long)Pal[0x3A] * 4 +
                                  (unsigned long)Gif->ImageLeft * 4;
            }
        }
        DataLen -= Len;
    }
}