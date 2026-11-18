int NeXTDecode(TIFF* tif, uint8_t* buf, int32_t occ) {
    uint8_t* bp = buf;
    int32_t cc = occ;
    uint8_t* op;
    int64_t lastpixel;
    int64_t count;
    uint8_t byte;
    int32_t scanline;
    int32_t pad;
    int32_t i;
    int32_t off;
    int32_t bits_left;

    // Zero out the output buffer
    while (cc > 0) {
        *bp++ = 0xff;
        cc--;
    }

    // Retrieve state from the TIFF structure
    uint8_t* tif_rawdata = *(uint8_t**)((char*)tif + 0x18);
    int64_t tif_rawcc = *(int64_t*)((char*)tif + 0x20);
    int64_t tif_rawdatasize = *(int64_t*)((char*)tif + 0x10);

    // Check if the strip size is a multiple of the scanline width
    if (occ % tif_rawdatasize != 0) {
        TIFFErrorExt(*(void**)((char*)tif + 0x28), "NeXTDecode", "Not enough data for scanline");
        return 0;
    }

    op = bp;
    while (tif_rawcc > 0 && occ > 0) {
        byte = *tif_rawdata++;
        tif_rawcc--;

        if (byte == 0) {
            if (tif_rawcc < tif_rawdatasize) {
                goto error;
            }
            _TIFFmemcpy(op, tif_rawdata, tif_rawdatasize);
            tif_rawdata += tif_rawdatasize;
            tif_rawcc -= tif_rawdatasize;
        } else if (byte == 0x40) {
            if (tif_rawcc < 4) {
                goto error;
            }
            off = (*tif_rawdata << 8) | *(tif_rawdata + 1);
            count = (*(tif_rawdata + 2) << 8) | *(tif_rawdata + 3);
            if (tif_rawcc < count + 4 || off + count > tif_rawdatasize) {
                goto error;
            }
            _TIFFmemcpy(op + off, tif_rawdata + 4, count);
            tif_rawdata += count + 4;
            tif_rawcc -= count + 4;
        } else {
            // 2-bit RLE decoding
            pad = *(int32_t*)((char*)tif + 0x4);
            if (*(uint32_t*)tif & 0x400) {
                pad = *(int32_t*)((char*)tif + 0x8);
            }

            op = bp;
            count = byte;
            do {
                off = (count >> 6) & 3;
                count = (count & 0x3F) - 1;
                for (i = 0; count >= 0 && i < pad; i++, count--) {
                    switch (i & 3) {
                        case 0:
                            *op = off << 6;
                            break;
                        case 1:
                            *op |= off << 4;
                            break;
                        case 2:
                            *op |= off << 2;
                            break;
                        case 3:
                            *op++ |= off;
                            break;
                    }
                }
                if (i >= pad) {
                    break;
                }
                if (tif_rawcc == 0) {
                    goto error;
                }
                byte = *tif_rawdata++;
                tif_rawcc--;
            } while (1);
        }

        occ -= tif_rawdatasize;
        op += tif_rawdatasize;
    }

    // Store back the updated pointers and sizes
    *(uint8_t**)((char*)tif + 0x18) = tif_rawdata;
    *(int64_t*)((char*)tif + 0x20) = tif_rawcc;
    return 1;

error:
    TIFFErrorExt(*(void**)((char*)tif + 0x28), "NeXTDecode", "Not enough data for scanline %d", *(int32_t*)((char*)tif + 0xC));
    return 0;
}