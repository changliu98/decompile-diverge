int cp_unfilter(int width, int height, int bpp, unsigned char* data) {
    int stride = width * bpp;
    unsigned char* prev_row = 0;

    if (height <= 0) {
        return 1;
    }

    // First row unfiltering
    unsigned char filter = *data++;
    if (filter > 4) {
        return 0;
    }

    switch (filter) {
        case 0:
            break;
        case 1:
            for (int i = bpp; i < stride; i++) {
                data[i] += data[i - bpp];
            }
            break;
        case 2:
            break;
        case 3:
            for (int i = bpp; i < stride; i++) {
                data[i] += data[i - bpp] / 2;
            }
            break;
        case 4:
            for (int i = bpp; i < stride; i++) {
                data[i] += cp_paeth(data[i - bpp], 0, 0);
            }
            break;
    }

    // Subsequent rows unfiltering
    for (int y = 1; y < height; y++) {
        prev_row = data;
        data += stride;
        
        filter = *data++;
        if (filter > 4) {
            return 0;
        }

        switch (filter) {
            case 0:
                break;
            case 1:
                for (int i = bpp; i < stride; i++) {
                    data[i] += data[i - bpp];
                }
                break;
            case 2:
                for (int i = 0; i < stride; i++) {
                    data[i] += prev_row[i];
                }
                break;
            case 3:
                for (int i = 0; i < bpp; i++) {
                    data[i] += prev_row[i] / 2;
                }
                for (int i = bpp; i < stride; i++) {
                    data[i] += (data[i - bpp] + prev_row[i]) / 2;
                }
                break;
            case 4:
                for (int i = 0; i < bpp; i++) {
                    data[i] += prev_row[i];
                }
                for (int i = bpp; i < stride; i++) {
                    data[i] += cp_paeth(data[i - bpp], prev_row[i], prev_row[i - bpp]);
                }
                break;
        }
    }

    return 1;
}