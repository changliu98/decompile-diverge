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
            *ThisRow->RasterBits.Red = *PixelBuf;
          PixelBuf++;
          ThisRow->RasterBits.Red++;
        }
      } else {
        for (i = ThisChunk; i > 0; i--) {
          if (*PixelBuf != GifFile->Image.TransparentColor)
            *ThisRow->RasterBits.Color =
                GifIndexToTrueColor(GifFile->SColorMap, *PixelBuf);
          PixelBuf++;
          ThisRow->RasterBits.Red += 4;
        }
      }
    } else {
      if (Private->ColorFlag & 1) {
        memcpy(ThisRow->RasterBits.Red, PixelBuf, ThisChunk);
        PixelBuf += ThisChunk;
        ThisRow->RasterBits.Red += ThisChunk;
      } else {
        for (i = ThisChunk; i > 0; i--) {
          *ThisRow->RasterBits.Color =
              GifIndexToTrueColor(GifFile->SColorMap, *PixelBuf++);
          ThisRow->RasterBits.Red += 4;
        }
      }
    }
    ThisRow->RemainingPixels -= ThisChunk;
    if (ThisRow->RemainingPixels == 0) {
      ThisRow->RemainingPixels = GifFile->AspectWidth;
      switch (ThisRow->DisposalMode) {
        case 0:
          ThisRow->Offset++;
          break;
        case 1:
          ThisRow->Offset += 8;
          if (ThisRow->Offset >= Private->Height) {
            ThisRow->DisposalMode++;
            ThisRow->Offset = GifFile->ImageLeft + 4;
          }
          break;
        case 2:
          ThisRow->Offset += 8;
          if (ThisRow->Offset >= Private->Height) {
            ThisRow->DisposalMode++;
            ThisRow->Offset = GifFile->ImageLeft + 2;
          }
          break;
        case 3:
          ThisRow->Offset += 4;
          if (ThisRow->Offset >= Private->Height) {
            ThisRow->DisposalMode++;
            ThisRow->Offset = GifFile->ImageLeft + 1;
          }
          break;
        case 4:
          ThisRow->Offset += 2;
          break;
      }
      if (Private->ColorFlag & 1) {
        ThisRow->RasterBits.Red =
            Private->Buffer.Red + ThisRow->Offset * Private->ByteWidth;
      } else {
        ThisRow->RasterBits.Red =
            Private->Buffer.Red + ThisRow->Offset * Private->ByteWidth * 4;
        ThisRow->RasterBits.Red += GifFile->ImageLeft * 4;
      }
    }
    PixelCount -= ThisChunk;
  }
}