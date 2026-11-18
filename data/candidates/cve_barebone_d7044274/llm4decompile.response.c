int
DGifSlurp(GifFileType * GifFile) {

    GifRecordType RecordType;
    int CodeSize,
            ImageNumber = 0;
    GifByteType *CodeBlock,
            *Extension;
    GifPixelType *Line;
    SavedImage *sp = 0;
    SavedImage noext, ext;

    memset(&noext, '\0', sizeof(SavedImage));
    noext.delay = 0;
    noext.dispose = 0;
    noext.iter = 1;
    noext.transp = -1;
    noext.ExtensionBlocks = 0;
    noext.ExtensionBlockCount = 0;
    memcpy(&ext, &noext, sizeof(SavedImage));

    GifFile->SavedImages = 0;

    do {
        if (!DGifGetRecordType(GifFile, &RecordType))
            return 0;

        switch (RecordType) {

            case IMAGE_DESC_RECORD_TYPE:

                if (DGifGetImageDesc(GifFile) == 0)
                    return 0;

                sp = &GifFile->SavedImages[GifFile->ImageCount - 1];
                ext.RasterBits = sp->RasterBits;
                ext.ImageDesc = sp->ImageDesc;
                memcpy(sp, &ext, sizeof(SavedImage));
                memcpy(&ext, &noext, sizeof(SavedImage));

                sp->RasterBits = (GifPixelType *) xmalloc(
                        (size_t) sp->ImageDesc.Width * (size_t) sp->ImageDesc.Height);

                if (sp->ImageDesc.Interlace) {
                    int Start,
                            Jumps;
                    for (Start = 0; Start < 4; Start++)
                        for (ImageNumber = DGifSlurp::InterlacedOffset[Start];
                                ImageNumber < sp->ImageDesc.Height;
                                ImageNumber += DGifSlurp::InterlacedJumps[Start]) {

                            if (DGifGetLine(GifFile,
                                    sp->RasterBits + ImageNumber * sp->ImageDesc.Width,
                                    sp->ImageDesc.Width) != 1)
                                return 0;
                        }
                } else {
                    if (DGifGetLine(GifFile, sp->RasterBits,
                            sp->ImageDesc.Width * sp->ImageDesc.Height) == 0)
                        return 0;
                }
                break;

            case EXTENSION_RECORD_TYPE:

                if (DGifGetExtension(GifFile, &CodeSize, &Extension) == 0)
                    return 0;
                if (Extension != 0) {
                    if (CodeSize & 0xff)
                        switch (CodeSize & 0xff) {

                            case 0xf9:

                                if (Extension[0] < 4) {
                                    _GifError = 114;
                                    return 0;
                                }
                                ext.dispose = Extension[1] >> 2;
                                ext.delay = Extension[2] | (Extension[3] << 8);
                                if ((Extension[1] & 0x1) == 0x1) {
                                    if (Extension[0] < 5) {
                                        _GifError = 114;
                                        return 0;
                                    }
                                    ext.transp = Extension[4];
                                }
                                break;

                            case 0xff:

                                if (Extension[0] < 4) {
                                    _GifError = 114;
                                    return 0;
                                }
                                ext.iter = Extension[2] | (Extension[3] << 8);
                                break;

                            default:

                                AddExtensionBlock(&ext, Extension[0],
                                        Extension + 1);
                                ext.ExtensionBlocks[ext.ExtensionBlockCount - 1].code =
                                        CodeSize;
                        }
                    else
                        AddExtensionBlock(&ext, Extension[0], Extension + 1);

                    while (DGifGetExtensionNext(GifFile, &Extension)
                            && Extension != 0)
                        AddExtensionBlock(sp, Extension[0], Extension + 1);

                    if (Extension != 0)
                        return 0;
                }
                break;

            case TERMINATE_RECORD_TYPE:

                break;

            default:

                break;
        }
    }
    while (RecordType != TERMINATE_RECORD_TYPE);

    return 1;
}