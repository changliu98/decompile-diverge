int MPEG12_ParseSeqHdr(const uint8_t *buf, int buf_size, int *width, int *height, int *aspect_ratio, double *frame_rate, uint32_t *bit_rate) {
    int ret = -1;
    *width = 0;
    int buf_size_adj = buf_size - 6;
    int bit_rate_val = 0;
    int i = 0;

    while (i < buf_size_adj) {
        uint32_t code = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];

        if (code == 0x000001b3) { // Sequence Header
            buf += 4;
            *width = (buf[0] << 4) | ((buf[1] >> 4) & 0xf);
            *height = ((buf[1] & 0xf) << 8) | buf[2];
            int aspect_ratio_info = (buf[3] >> 4) & 0xf;

            if (aspect_ratio) {
                uint32_t ar_val = 0;
                switch (aspect_ratio_info) {
                    case 2:
                        ar_val = (4 << 16) | 3;
                        break;
                    case 3:
                        ar_val = (16 << 16) | 9;
                        break;
                    case 4:
                        ar_val = (2 << 16) | 21; // 2.21:1 represented as 0x00020015
                        break;
                    default:
                        ar_val = 0;
                        break;
                }
                *aspect_ratio = ar_val;
            }

            int frame_rate_code = buf[3] & 0xf;
            *frame_rate = mpeg12_frame_rate_table[frame_rate_code];

            bit_rate_val = (buf[4] << 10) | (buf[5] << 2) | (buf[6] >> 6);
            *bit_rate = (double)bit_rate_val * 400.0;

            i += 11;
            buf += 7;
            ret = 0;
        } else if (ret == 0) {
            if (code == 0x000001b5) { // Extension Header
                buf += 4;
                i += 4;

                if (((buf[0] >> 4) - 1) == 0) { // Sequence Display Extension
                    *width = 1;
                    *height = ((buf[1] & 1) << 13) | ((buf[2] & 0x80) << 5) | (*height & 0xfff);
                    *aspect_ratio = ((buf[2] & 0x60) << 7) | (*aspect_ratio & 0xfff);
                    
                    uint32_t vbv = ((buf[2] & 0x1f) << 7) | (buf[3] >> 1);
                    bit_rate_val = (vbv << 18) | bit_rate_val;
                    *bit_rate = (double)bit_rate_val * 400.0;
                }
                buf += 1;
                i += 1;
            } else {
                if (code == 0x00000100) { // Picture Start Code
                    return ret;
                }
            }
        }

        i += 1;
        buf += 1;
    }

    return ret;
}