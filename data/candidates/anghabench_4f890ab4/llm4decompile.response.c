int ff_norm_qscale(int qscale, enum AVPixelFormat pix_fmt)
{
    switch (pix_fmt) {
    case AV_PIX_FMT_YUV420P:
        return qscale >> 2;
    case AV_PIX_FMT_YUV422P:
        return qscale >> 1;
    case AV_PIX_FMT_YUV444P:
        return qscale;
    case AV_PIX_FMT_YUV410P:
        return (64 - qscale) >> 2;
    default:
        return qscale;
    }
}