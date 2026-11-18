int stbi__tga_get_comp(int bpp, int is_grayscale, int *is_rgb16_flag)
{
    // Initialize the is_rgb16 flag to 0 if the pointer is valid
    if (is_rgb16_flag)
        *is_rgb16_flag = 0;

    // Determine the number of components based on bits per pixel
    switch (bpp) {
    case 8:
        // 8-bit grayscale images have 1 component
        return 1;
    case 0x10: // 16 bits per pixel
        if (is_grayscale)
            // 16-bit grayscale images have 2 components (16-bit grey)
            return 2;
        /* fall through */
    case 0xf: // 15 bits per pixel (often treated as 16-bit RGB)
        if (is_rgb16_flag)
            // Mark that this is an RGB16 format
            *is_rgb16_flag = 1;
        // 15/16-bit RGB images have 3 components
        return 3;
    case 0x18: // 24 bits per pixel
    case 0x20: // 32 bits per pixel
        // Return the number of components (3 for 24-bit, 4 for 32-bit)
        return bpp / 8;
    default:
        // Unsupported bit depth
        return 0;
    }
}