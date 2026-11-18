void tigrFill(TImage *image, int x, int y, int width, int height, TPixel color)
{
    TPixel *pixel;
    int i, j, pitch;

    if (x < 0) {
        width += x;
        x = 0;
    }
    if (y < 0) {
        height += y;
        y = 0;
    }
    if (x + width > image->width)
        width = image->width - x;
    if (y + height > image->height)
        height = image->height - y;
    if ((width <= 0) || (height <= 0))
        return;

    pixel = image->data + y * image->width + x;
    pitch = image->width;
    for (j = height; --j; pixel += pitch) {
        for (i = 0; i < width; ++i)
            pixel[i] = color;
    }
}