int DGifSlurp(GifFileType *GifFile) {
    int RecordType;
    int ExtCode;
    unsigned char *Extension;
    SavedImage *sp;
    SavedImage temp_save;

    memset(&temp_save, 0, sizeof(SavedImage));

    GifFile->SavedImages = NULL;

    while (1) {
        if (DGifGetRecordType(GifFile, &RecordType) == 0) {
            return 0;
        }

        if (RecordType == 4) { // TERMINATE_RECORD_TYPE
            return 1;
        }

        switch (RecordType) {
            case 2: { // IMAGE_DESC_RECORD_TYPE
                if (DGifGetImageDesc(GifFile) == 0) {
                    return 0;
                }

                sp = &GifFile->SavedImages[GifFile->ImageCount - 1];
                
                // Allocate memory for pixel data
                sp->RasterBits = xmalloc(sp->Width * sp->Height);

                if (sp->Interlace) {
                    int i, j;
                    // Read interlaced image data
                    for (i = 0; i < 4; i++) {
                        for (j = InterlacedOffset[i]; j < sp->Height; j += InterlacedJumps[i]) {
                            if (DGifGetLine(GifFile, sp->RasterBits + j * sp->Width, sp->Width) != 1) {
                                return 0;
                            }
                        }
                    }
                } else {
                    // Read non-interlaced image data
                    if (DGifGetLine(GifFile, sp->RasterBits, sp->Width * sp->Height) == 0) {
                        return 0;
                    }
                }
                break;
            }

            case 3: { // EXTENSION_RECORD_TYPE
                if (DGifGetExtension(GifFile, &ExtCode, &Extension) == 0) {
                    return 0;
                }

                while (Extension != NULL) {
                    if (ExtCode == 0xf9) { // Graphics Control Extension
                        if (Extension[0] < 4) {
                            _GifError = 0x72; // D_GIF_ERR_NO_SCRN_DSCR
                            return 0;
                        }
                        
                        // Extract GCE fields (Disposal, DelayTime, TransparentColor)
                        // temp_save.Disposal = (Extension[1] >> 2);
                        // temp_save.DelayTime = Extension[2] | (Extension[3] << 8);
                        // if (Extension[1] & 1) {
                        //     if (Extension[0] >= 5) {
                        //         temp_save.TransparentColor = Extension[4];
                        //     } else {
                        //         _GifError = 0x72;
                        //         return 0;
                        //     }
                        // }
                    } else if (ExtCode == 0xff) { // Application Extension
                        if (Extension[0] < 4) {
                            _GifError = 0x72;
                            return 0;
                        }
                        // Extract Application Extension fields
                        // temp_save.ApplicationDelay = Extension[2] | (Extension[3] << 8);
                    } else {
                        // Add generic extension block
                        if (AddExtensionBlock(&temp_save, Extension[0], Extension + 1) == 0) {
                            return 0;
                        }
                        // Update the extension's function code
                        // temp_save.ExtensionBlocks[temp_save.ExtensionBlockCount - 1].Function = ExtCode;
                    }

                    if (DGifGetExtensionNext(GifFile, &Extension) == 0) {
                        return 0;
                    }
                }
                break;
            }

            default:
                break;
        }
    }
}