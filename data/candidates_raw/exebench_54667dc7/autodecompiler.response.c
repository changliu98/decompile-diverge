static void
compute_clip(int x, int w, int max_x, int *clip_x, int *clip_w)
{
    int x1 = x;
    int x2 = x + w;

    *clip_x = 0;
    *clip_w = 0;

    if ((x1 > max_x) || (x2 < 0) || (w < 2))
 return;

    if (x1 < 0)
 x1 = 0;

    if (x2 > max_x)
 x2 = max_x;

    *clip_x = x1;
    *clip_w = x2 - x1;
}