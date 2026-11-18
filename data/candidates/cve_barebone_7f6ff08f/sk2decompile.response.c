static void WritePixels(GifFileType *GifFile, GifRowType *ThisRow,
                        unsigned char *PixelBuf, int PixelCount) {
  GifFilePrivateType *Private = GifFile->Private;
  int ThisChunk;
  int i;
  while (PixelCount) {
    if (ThisRow->RemainingPixels < PixelCount)
      ThisChunk = ThisRow->RemainingPixels;
    else
      ThisChunk = PixelCount;
    if (GifFile->Image.ColorResolution & 0x10) {
      if (Private->ColorFlag & 1) {
        for (i = ThisChunk; i > 0; i--) {
          if (*PixelBuf != GifFile->Image.TransparentColor)
            *ThisRow->Packed.Red = *PixelBuf;
          PixelBuf++;
          ThisRow->Packed.Red++;
        }
      } else {
        for (i = ThisChunk; i > 0; i--) {
          if (*PixelBuf != GifFile->Image.TransparentColor)
            *ThisRow->Packed.RGBA =
                GifIndexToTrueColor(GifFile->SColorMap, *PixelBuf);
          PixelBuf++;
          ThisRow->Packed.Red += 4;
        }
      }
    } else {
      if (Private->ColorFlag & 1) {
        memcpy(ThisRow->Packed.Red, PixelBuf, ThisChunk);
        PixelBuf += ThisChunk;
        ThisRow->Packed.Red += ThisChunk;
      } else {
        for (i = ThisChunk; i > 0; i--) {
          *ThisRow->Packed.RGBA =
              GifIndexToTrueColor(GifFile->SColorMap, *PixelBuf++);
          ThisRow->Packed.Red += 4;
        }
      }
    }
    ThisRow->RemainingPixels -= ThisChunk;
    if (ThisRow->RemainingPixels == 0) {
      ThisRow->RemainingPixels = GifFile->AspectByteCount;
      switch (ThisRow->ByteCountIndex) {
        case 0:
          ThisRow->ByteCount++;
          break;
        case 1:
          ThisRow->ByteCount += 8;
          if (ThisRow->ByteCount >= Private->Width) {
            ThisRow->ByteCountIndex++;
            ThisRow->ByteCount = GifFile->PixelCount + 4;
          }
          break;
        case 2:
          ThisRow->ByteCount += 8;
          if (ThisRow->ByteCount >= Private->Width) {
            ThisRow->ByteCountIndex++;
            ThisRow->ByteCount = GifFile->PixelCount + 2;
          }
          break;
        case 3:
          ThisRow->ByteCount += 4;
          if (ThisRow->ByteCount >= Private->Width) {
            ThisRow->ByteCountIndex++;
            ThisRow->ByteCount = GifFile->PixelCount + 1;
          }
          break;
        case 4:
          ThisRow->ByteCount += 2;
          break;
      }
      if (Private->ColorFlag & 1) {
        ThisRow->Packed.Red =
            Private->Buffer.Red + ThisRow->ByteCount * Private->BytesPerPixel;
      } else {
        ThisRow->Packed.Red = Private->Buffer.Red +
                              ThisRow->ByteCount * Private->BytesPerPixel * 4;
        ThisRow->Packed.Red += GifFile->BGIndex * 4;
      }
    }
    PixelCount -= ThisChunk;
  }
}