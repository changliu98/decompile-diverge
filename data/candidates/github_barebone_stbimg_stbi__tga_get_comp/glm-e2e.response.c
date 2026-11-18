int stbi__tga_get_comp(int bits_per_pixel, int is_grey, int *retval) {
    int comp = 0;

    if (retval != 0) {
        *retval = 0;
    }

    switch (bits_per_pixel - 8) {
        case 0: // 8 bits per pixel
            comp = 1;
            break;
        case 8: // 16 bits per pixel
            if (is_grey != 0) {
                comp = 2;
            } else {
                if (retval != 0) {
                    *retval = 1;
                }
                comp = 3;
            }
            break;
        case 16: // 24 bits per pixel
            comp = 3;
            break;
        case 24: // 32 bits per pixel
            comp = 4;
            break;
        default:
            // For any other bit depth (including 0), it divides by 8
            comp = bits_per_pixel / 8;
            break;
    }

    return comp;
}