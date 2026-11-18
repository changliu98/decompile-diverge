float __cdecl KBND_REPLICATE(const float *img, int w, int h, int x, int y, float bnd_const)
{
    int clamped_x = x;
    int clamped_y = y;

    // Clamp the x-coordinate to the valid image bounds [0, w-1]
    if (x < 0)
        clamped_x = 0;
    if (clamped_x >= w)
        clamped_x = w - 1;

    // Clamp the y-coordinate to the valid image bounds [0, h-1]
    if (y < 0)
        clamped_y = 0;
    if (clamped_y >= h)
        clamped_y = h - 1;

    // Return the pixel value at the clamped coordinates
    return img[clamped_x + w * clamped_y];
}