int clip_img(int clip_x1, int clip_y1, int clip_x2, int clip_y2,
          int *x, int *y, int *w, int *h, int sx, int sy)
{
    char ok = 1;

    if (*x < clip_x1) {
        *w -= clip_x1 - *x;
        *sx += sx * (clip_x1 - *x);
        *x = clip_x1;
    }
    if (*w > clip_x2 - *x + 1)
        *w = clip_x2 - *x + 1;

    if (*y < clip_y1) {
        *h -= clip_y1 - *y;
        *sy += sy * (clip_y1 - *y);
        *y = clip_y1;
    }
    if (*h > clip_y2 - *y + 1)
        *h = clip_y2 - *y + 1;

    ok &= (*w >= 0) & (*h >= 0);

    return ok;
}