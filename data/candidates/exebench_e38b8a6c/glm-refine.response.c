bool __cdecl clip_img(
        int clip_x1,               // Left boundary of the clipping region
        int clip_y1,               // Top boundary of the clipping region
        int clip_x2,               // Right boundary of the clipping region (inclusive)
        int clip_y2,               // Bottom boundary of the clipping region (inclusive)
        int *x,                    // Destination X position (in/out)
        int *y,                    // Destination Y position (in/out)
        int *w,                    // Destination width (in/out)
        int *h,                    // Destination height (in/out)
        int *sx,                   // Source X offset (in/out)
        int *sy,                   // Source Y offset (in/out)
        int mx,                    // Source X multiplier (e.g., bytes per pixel)
        int my)                    // Source Y multiplier (e.g., bytes per row)
{
    // Clip X-axis (Left boundary)
    if (*x < clip_x1)
    {
        int delta_x = clip_x1 - *x;
        *w -= delta_x;
        *sx += mx * delta_x;
        *x = clip_x1;
    }

    // Clip X-axis (Right boundary)
    // The +1 indicates that clip_x2 is an inclusive boundary
    if (*w > clip_x2 - *x + 1)
        *w = clip_x2 - *x + 1;

    // Clip Y-axis (Top boundary)
    if (*y < clip_y1)
    {
        int delta_y = clip_y1 - *y;
        *h -= delta_y;
        *sy += my * delta_y;
        *y = clip_y1;
    }

    // Clip Y-axis (Bottom boundary)
    // The +1 indicates that clip_y2 is an inclusive boundary
    if (*h > clip_y2 - *y + 1)
        *h = clip_y2 - *y + 1;

    // The rectangle is valid only if both width and height are non-negative
    return (*w >= 0) && (*h >= 0);
}