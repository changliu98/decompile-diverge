static int MPEG12_ParseSeqHdr(unsigned char *buf, unsigned int len,
                                     int *is_mpeg2, unsigned int *width,
                                     unsigned int *height, double *fps,
                                     double *bitrate, unsigned int *aspect_ratio)
{
    int found = -1;
    unsigned int code, aspect_code, framerate_code, bitrate_ext, bitrate_int;
    unsigned int par, i;

    *is_mpeg2 = 0;

    len -= 6;
    bitrate_int = 0;
    for (i = 0; ; i++) {
        if (i >= len)
            break;
        code = (((unsigned int) buf[0]) << 24) | (((unsigned int) buf[1]) << 16) |
               (((unsigned int) buf[2]) << 8) | ((unsigned int) buf[3]);
        if (code == 0x000001B3) {

            buf += 4;
            *width = buf[0];
            *width <<= 4;
            *width |= (buf[1] >> 4) & 0x0F;
            *height = buf[1] & 0x0F;
            *height <<= 8;
            *height |= buf[2];
            aspect_code = (buf[3] >> 4) & 0x0F;
            if (aspect_ratio != NULL) {
                par = 0;
                switch (aspect_code) {
                    case 0:
                        *aspect_ratio = 0;
                        break;
                    case 1:
                        par = 4;
                        par <<= 16;
                        par |= 3;
                        break;
                    case 2:
                        par = 16;
                        par <<= 16;
                        par |= 9;
                        break;
                    case 3:
                        par = 2;
                        par <<= 16;
                        par |= 21;
                        break;
                    default:
                        *aspect_ratio = 0;
                        break;
                }
                *aspect_ratio = par;
            }
            framerate_code = buf[3] & 0x0F;
            *fps = mpeg12_frame_rate_table[framerate_code];
            bitrate_int = (buf[4] << 10) | (buf[5] << 2) | (buf[6] >> 6);
            *bitrate = bitrate_int;
            *bitrate *= 400.0;
            i += 11;
            buf += 7;
            found = 0;
        } else if (found == 0 && code == 0x000001B5) {

            buf += 4;
            i += 4;
            switch ((buf[0] >> 4) - 1) {
                case 0:

                    *is_mpeg2 = 1;
                    *height = (*height & 0xFFF) | ((buf[1] & 0x01) << 13) | ((buf[2] & 0xFE) << 5);
                    *width = (*width & 0xFFF) | ((buf[2] & 0x60) << 7);
                    bitrate_ext = (buf[2] & 0x1F) << 7;
                    bitrate_ext |= buf[3] >> 1;
                    bitrate_int |= bitrate_ext << 18;
                    *bitrate = bitrate_int;
                    *bitrate *= 400.0;
                    break;
                default:

                    break;
            }
            buf++;
            i++;
        } else if (code == 0x00000100) {
            found = i;
            break;
        } else if (found != 0) {
            continue;
        }
    }

    return found;
}