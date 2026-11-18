void calculate_proportions(int src_w, int src_h, int *dst_w, int *dst_h)
{
    int w = (dst_w != ((void *)0)) ? *dst_w : 0;
    int h = (dst_h != ((void *)0)) ? *dst_h : 0;
    if (src_w > 0 && src_w >= src_h && (w > 0 || h <= 0)) {
        h = (src_h * w) / src_w;
    } else if (src_h > 0) {
        w = (src_w * h) / src_h;
    }
    if (dst_w != ((void *)0)) {
        *dst_w = w;
    }
    if (dst_h != ((void *)0)) {
        *dst_h = h;
    }
}