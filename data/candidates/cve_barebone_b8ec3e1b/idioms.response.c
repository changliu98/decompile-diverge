static int xpm_decode_frame(struct AVCodecContext *avctx, void *data, int *got_frame, struct AVPacket *avpkt)
{
    struct XPMDecContext *ctx = avctx->priv_data;
    char *p = avpkt->data;
    char *end = p + avpkt->size;
    int i;
    int j;
    int ncolors;
    int cpp;
    char *line;
    char *endline;
    int *dst;
    char *color;
    char *color_end;
    char *color_name;
    char *color_text;
    int color_index;
    int ret;
    avctx->pix_fmt = PIX_FMT_RGB1;
    for (;;) {
        int found = 0;
        if (strstart(p, "/* XPM */", sizeof("/* XPM */") - 1))
            found = p < (end - (sizeof("/* XPM */") - 1));
        if (found)
            p++;
        else
            break;
    }
    if (p >= end) {
        av_log(avctx, AV_LOG_ERROR, "missing signature\n");
        return -1094995529;
    }
    line = p + strstr_len(p, "\"");
    if (xpmdec_get_int() != 4) {
        av_log(avctx, AV_LOG_ERROR, "missing image parameters\n");
        return -1094995529;
    }
    ret = xpmdec_alloc_image(avctx, avctx->width, avctx->height);
    if (ret < 0)
        return ret;
    ret = xpmdec_alloc_frame(avctx, data, 0);
    if (ret < 0)
        return ret;
    if (cpp < 1 || cpp > 4) {
        av_log(avctx, AV_LOG_ERROR, "unsupported/invalid number of chars per pixel: %d\n", cpp);
        return -1094995529;
    }
    if (ncolors < 1 || ncolors > (1 * 94 * 94 * 94 * 94)) {
        av_log(avctx, AV_LOG_ERROR, "invalid number of colors: %d\n", ncolors);
        return -1094995529;
    }
    xpmdec_alloc(ctx, &ctx->pixels_size, ncolors * 4);
    if (!ctx->pixels)
        return -12;
    line = line + strstr_len(line, ",") + 1;
    for (i = 0; i < ncolors; i++) {
        color = line + strstr_len(line, "\"") + 1;
        if (color + cpp > end)
            return -1094995529;
        color_end = color + cpp;
        color = (char *) xpmdec_to_int(color, cpp);
        if (color < 0)
            return color;
        color_index = xpmdec_to_index(color, cpp);
        if (color_index < 0)
            return color_index;
        ctx->pixels[color_index] = xpmdec_to_color(&color_end, &color_name);
        line = color_end + strstr_len(color_end, ",") + 1;
    }
    for (i = 0; i < avctx->height; i++) {
        dst = ((struct AVPicture *) (data))->data[0] + i * ((struct AVPicture *) (data))->linesize[0];
        line = line + strstr_len(line, "\"") + 1;
        for (j = 0; j < avctx->width; j++) {
            if (line + cpp > end)
                return -1094995529;
            color_index = xpmdec_to_index(line, cpp);
            if (color_index < 0)
                return color_index;
            *dst++ = ctx->pixels[color_index];
            line += cpp;
        }
        line = line + strstr_len(line, ",") + 1;
    }
    ((struct AVPicture *) (data))->coded_height = 1;
    ((struct AVPicture *) (data))->coded_width = 1;
    *got_frame = 1;
    return avpkt->size;
}