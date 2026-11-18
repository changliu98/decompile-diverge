int
clip_wh(int *x, int *width, int min_width, int max_width)
{
    int adjust;

    if (*x < min_width) {
 adjust = min_width - *x;
 *width += *x - min_width;
 *x = min_width;
    } else {
 adjust = 0;
 if (*x + *width >= max_width)
     *width = max_width - *x;
    }
    return adjust;
}