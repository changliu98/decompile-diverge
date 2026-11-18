void subpixels(unsigned_long pixel_value, unsigned_long *alpha, unsigned_long *red, unsigned_long *green, unsigned_long *blue)
{
    // Extract the alpha channel (most significant byte)
    *alpha = pixel_value >> 0x18 & 0xff;
    // Extract the red channel
    *red = pixel_value >> 0x10 & 0xff;
    // Extract the green channel
    *green = pixel_value >> 8 & 0xff;
    // Extract the blue channel (least significant byte)
    *blue = pixel_value & 0xff;
}