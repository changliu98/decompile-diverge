static int stbi__tga_get_comp(int bpp, int grey, int *rgb16)
{
    int size;

    if (rgb16) *rgb16 = 0;
    switch(bpp) {
    case 8:
        size = 1;
        break;
    case 16:
        if (grey) {
            size = 2;
        } else {

            goto rgb16_case;
        }
    case 15:
        if (rgb16) *rgb16 = 1;
        size = 3;
        break;
    case 24:
    case 32:
        size = bpp / 8;
        break;
    default:
        size = 0;
    }
    return size;

 rgb16_case:
    if (rgb16) *rgb16 = 1;
    size = 3;
    return size;
}