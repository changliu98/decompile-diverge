int nsgif__deinterlace(unsigned height, unsigned *y, unsigned char *step)
{
    *y += (*step & 0xf);
    if (*y >= height) {
        if (*step == 4) {
            *y = 1;
            *step = 2;
        } else if (*step == 8) {
            *y = 2;
            *step = 4;
        } else if (*step == 0x18) {
            *y = 4;
            *step = 8;
        } else {
            return 0;
        }
    }
    if (*y >= height) {
        return nsgif__deinterlace(height, y, step);
    }
    return 1;
}