void subpixels(uint32_t pixel, uint8_t *alpha, uint8_t *red, uint8_t *green, uint8_t *blue)
{
    *alpha = (pixel >> 24) & 0xff;
    *red = (pixel >> 16) & 0xff;
    *green = (pixel >> 8) & 0xff;
    *blue = (pixel >> 0) & 0xff;
}