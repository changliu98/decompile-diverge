static int stbi__tga_get_comp(int format, int is_chroma, int *bits_per_sample)
{
    static const int bits_per_pixel[] = { 8, 16, 16, 16, 32, 32, 32, 32 };
    int bps;

    if (bits_per_sample)
        *bits_per_sample = 0;

    switch (format)
    {
    case V4L2_PIX_FMT_NV12:
        bps = is_chroma? 1 : 2;
        break;
    case V4L2_PIX_FMT_NV21:
        bps = is_chroma? 2 : 1;
        break;
    case V4L2_PIX_FMT_NV16:
    case V4L2_PIX_FMT_NV61:
        bps = is_chroma? 2 : 1;
        break;
    case V4L2_PIX_FMT_NV24:
    case V4L2_PIX_FMT_NV42:
        bps = is_chroma? 1 : 2;
        break;
    default:
        bps = 0;
    }

    if (bits_per_sample)
        *bits_per_sample = bps;

    return bps? bits_per_pixel[bps - 8] : 0;
}