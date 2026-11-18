int __cdecl stbi__bmp_set_mask_defaults(stbi__bmp_data *info, int compress)
{
    // Compression type 3 expects masks to be explicitly defined in the file.
    if (compress == 3)
        return 1;

    // For any other compression type (except 0), do nothing.
    if (compress != 0)
        return 0;

    // Uncompressed (compress == 0): set default masks based on bits per pixel
    if (info->bpp == 16)
    {
        // 5-bit Red, 5-bit Green, 5-bit Blue (0x7C00, 0x03E0, 0x001F)
        info->mr = 0x7C00;
        info->mg = 0x03E0;
        info->mb = 0x001F;
    }
    else if (info->bpp == 32)
    {
        // 8-bit per channel: 0xFF0000, 0x00FF00, 0x0000FF
        info->mr = 0x00FF0000;
        info->mg = 0x0000FF00;
        info->mb = 0x000000FF;
        info->ma = 0xFF000000; // -16777216 as unsigned 32-bit hex
        info->all_a = 0;
    }
    else
    {
        // Clear all masks for unsupported bit depths
        info->ma = 0;
        info->mb = 0;
        info->mg = 0;
        info->mr = 0;
    }

    return 1;
}