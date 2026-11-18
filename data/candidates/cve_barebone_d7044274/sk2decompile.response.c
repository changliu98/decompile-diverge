int DGifSlurp(GifFileType *GifFile) {
  GifRecordType RecordType;
  SavedImage *sp = NULL;
  SavedImage s;
  SavedImage si;
  int pass;
  unsigned char Function;
  unsigned char *Block;
  unsigned int Width, i;
  memset(&s, 0, sizeof(s));
  s.UserInputFlag = 0;
  s.ColorResolution = 0;
  s.SortFlag = 1;
  s.DisposalMode = -1;
  s.ExtensionBlocks = NULL;
  s.ExtensionBlockCount = 0;
  memcpy(&si, &s, sizeof(si));
  GifFile->SavedImages = NULL;
  for (;;) {
    if (!DGifGetRecordType(GifFile, &RecordType)) return 0;
    if (RecordType == IMAGE_DESC_RECORD_TYPE) {
      if (!DGifGetImageDesc(GifFile)) return 0;
      sp = &GifFile->SavedImages[GifFile->ImageCount - 1];
      si.RasterBits = sp->RasterBits;
      si.ColorMap = sp->ColorMap;
      si.Width = sp->Width;
      si.Height = sp->Height;
      si.ColorResolution = sp->ColorResolution;
      memcpy(sp, &si, sizeof(SavedImage));
      memcpy(&si, &s, sizeof(si));
      sp->RasterBits = (unsigned char *)xmalloc(
          (long)sp->Width * (long)sp->Height);
      if (sp->Height) {
        Width = sp->Width;
        i = sp->Height;
        for (pass = 0; pass < 4; pass++) {
          for (i = pass_height[pass]; i < Width; i += pass_incr[pass]) {
            if (DGifGetLine(GifFile, sp->RasterBits + i, Width) != 1) return 0;
          }
        }
      } else {
        if (!DGifGetLine(GifFile, sp->RasterBits, sp->Width * sp->Height))
          return 0;
      }
    } else if (RecordType == EXTENSION_RECORD_TYPE) {
      if (!DGifGetExtension(GifFile, &Function, &Block)) return 0;
      if (Block == NULL) break;
      switch (Function) {
        case 255:
          if (Block[0] < 4) {
            _GifError = 114;
            return 0;
          }
          si.SortFlag = Block[1] >> 2;
          si.UserInputFlag = *((unsigned short *)(Block + 1));
          if ((Block[1] & 1) == 1) {
            if (Block[0] < 5) {
              _GifError = 114;
              return 0;
            }
            si.DisposalMode = Block[4];
          }
          break;
        case 249:
          if (Block[0] < 4) {
            _GifError = 114;
            return 0;
          }
          si.ColorResolution = Block[1] >> 2;
          si.UserInputFlag = *((unsigned short *)(Block + 1));
          break;
        default:
          AddExtensionBlock(&si, Block[0], Block + 1);
          si.ExtensionBlocks[si.ExtensionBlockCount - 1].Function = Function;
          break;
      }
      while (DGifGetExtensionNext(GifFile, &Block)) {
        if (Block == NULL) break;
        AddExtensionBlock(sp, Block[0], Block + 1);
      }
    } else if (RecordType == TERMINATE_RECORD_TYPE) {
      break;
    }
  }
  return 1;
}