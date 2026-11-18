int DGifSlurp(GifFileType *GifFile)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  GifPixelType *pGVar4;
  uint Width;
  uint Height;
  uint j;
  uint i;
  GifByteType *ExtData;
  SavedImage noext;
  SavedImage ext;
  SavedImage *sp;
  GifRecordType RecordType;
  int ext_code;
  GifFileType *GifFile_local;
  
  sp = (SavedImage *)0x0;
  GifFile_local = GifFile;
  memset(&noext,0,0x40);
  noext.delay = 0;
  noext.dispose = '\0';
  noext.iter = 1;
  noext.transp = -1;
  noext.ExtensionBlocks = (ExtensionBlock *)0x0;
  noext.ExtensionBlockCount = 0;
  memcpy(&ext,&noext,0x40);
  GifFile_local->SavedImages = (SavedImage *)0x0;
  do {
    iVar2 = DGifGetRecordType(GifFile_local,&RecordType);
    if (iVar2 == 0) {
      return 0;
    }
    if (RecordType == IMAGE_DESC_RECORD_TYPE) {
      iVar2 = DGifGetImageDesc(GifFile_local);
      if (iVar2 == 0) {
        return 0;
      }
      sp = GifFile_local->SavedImages + (GifFile_local->ImageCount + -1);
      ext.RasterBits = sp->RasterBits;
      ext.ImageDesc.Left = (sp->ImageDesc).Left;
      ext.ImageDesc.Top = (sp->ImageDesc).Top;
      ext.ImageDesc.Width = (sp->ImageDesc).Width;
      ext.ImageDesc.Height = (sp->ImageDesc).Height;
      ext.ImageDesc.Interlace = (sp->ImageDesc).Interlace;
      ext.ImageDesc._20_4_ = *(undefined4 *)&(sp->ImageDesc).field_0x14;
      ext.ImageDesc.ColorMap = (sp->ImageDesc).ColorMap;
      memcpy(sp,&ext,0x40);
      memcpy(&ext,&noext,0x40);
      pGVar4 = xmalloc((long)(sp->ImageDesc).Width * (long)(sp->ImageDesc).Height);
      sp->RasterBits = pGVar4;
      if ((sp->ImageDesc).Interlace == 0) {
        iVar2 = DGifGetLine(GifFile_local,sp->RasterBits,
                            (sp->ImageDesc).Width * (sp->ImageDesc).Height);
        if (iVar2 == 0) {
          return 0;
        }
      }
      else {
        uVar1 = (sp->ImageDesc).Height;
        iVar2 = (sp->ImageDesc).Width;
        for (i = 0; i < 4; i = i + 1) {
          for (j = DGifSlurp::InterlacedOffset[i]; j < uVar1; j = DGifSlurp::InterlacedJumps[i] + j)
          {
            iVar3 = DGifGetLine(GifFile_local,sp->RasterBits + iVar2 * j,iVar2);
            if (iVar3 != 1) {
              return 0;
            }
          }
        }
      }
    }
    else if (RecordType == EXTENSION_RECORD_TYPE) {
      iVar2 = DGifGetExtension(GifFile_local,&ext_code,&ExtData);
      if (iVar2 == 0) {
        return 0;
      }
      if (ExtData != (GifByteType *)0x0) {
        if ((ext_code & 0xffU) == 0xf9) {
          if (*ExtData < 4) {
            _GifError = 0x72;
            return 0;
          }
          ext.dispose = (uchar)((int)(uint)ExtData[1] >> 2);
          ext.delay = *(unsigned_short *)(ExtData + 2);
          if ((ExtData[1] & 1) == 1) {
            if (*ExtData < 5) {
              _GifError = 0x72;
              return 0;
            }
            ext.transp = (short)ExtData[4];
          }
        }
        else if ((ext_code & 0xffU) == 0xff) {
          if (*ExtData < 4) {
            _GifError = 0x72;
            return 0;
          }
          ext.iter = *(unsigned_short *)(ExtData + 2);
        }
        else {
          AddExtensionBlock(&ext,(uint)*ExtData,ExtData + 1);
          ext.ExtensionBlocks[ext.ExtensionBlockCount + -1].code = ext_code;
        }
        while( true ) {
          iVar2 = DGifGetExtensionNext(GifFile_local,&ExtData);
          if (iVar2 == 0) {
            return 0;
          }
          if (ExtData == (GifByteType *)0x0) break;
          AddExtensionBlock(sp,(uint)*ExtData,ExtData + 1);
        }
      }
    }
  } while (RecordType != TERMINATE_RECORD_TYPE);
  return 1;
}