int xpm_decode_frame(AVCodecContext *avctx, void *data,
                            int *got_frame, AVPacket *avpkt)
{
    AVFrame *frame = data;
    XPMDecContext *s = avctx->priv_data;
    const uint8_t *buf = avpkt->data;
    const uint8_t *buf_end = buf + avpkt->size;
    const uint8_t *ptr;
    uint32_t *pixels;
    int width, height, ncolors, cpp, i, j, ret;
    int64_t size;

    avctx->pix_fmt = 1;

    /* find the start of the XPM data */
    for (ptr = buf; memcmp(ptr, "/* XPM */", 9) && ptr < buf_end - 9; ptr++);
    if (ptr >= buf_end) {
        av_log(avctx, 16, "missing signature\n");
        return -0x41444E49;
    }

    /* parse the image parameters */
    ptr += mod_strcspn(ptr, "\"");
    if (__isoc99_sscanf(ptr, "\"%u %u %u %u\",",
                        &avctx->width, &avctx->height, &ncolors, &cpp) != 4) {
        av_log(avctx, 16, "missing image parameters\n");
        return -0x41444E49;
    }

    if ((ret = ff_set_dimensions(avctx, avctx->width, avctx->height)) < 0 ||
        (ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    if (cpp < 1 || cpp > 4) {
        av_log(avctx, 16, "unsupported/invalid number of chars per pixel: %d\n", cpp);
        return -0x41444E49;
    }

    size = 1;
    for (i = 0; i < cpp; i++)
        size *= 94;

    if (ncolors < 1 || ncolors > size) {
        av_log(avctx, 16, "invalid number of colors: %d\n", ncolors);
        return -0x41444E49;
    }

    av_fast_padded_malloc(&s->pixels, &s->pixels_size, ncolors * sizeof(uint32_t));
    if (!s->pixels)
        return -12;

    /* parse the color table */
    ptr += mod_strcspn(ptr, ",") + 1;
    for (i = 0; i < ncolors; i++) {
        const uint8_t *ch = ptr;
        const uint8_t *cstr;
        int len, index;

        ptr += mod_strcspn(ptr, "\"") + 1;
        if (ptr + cpp > buf_end)
            return -0x41444E49;

        cstr = ptr;
        ptr += cpp;

        cstr = strstr(ptr, "c ");
        if (!cstr)
            return -0x41444E49;
        cstr += 2;
        len = strcspn(cstr, "\" ");

        index = ascii2index(ch, cpp);
        if (index < 0)
            return index;

        s->pixels[index] = color_string_to_rgba(cstr, len);

        ptr += mod_strcspn(ptr, ",") + 1;
    }

    /* parse the image data */
    for (height = 0; height < avctx->height; height++) {
        pixels = (uint32_t *)frame->data[0] + height * frame->linesize[0] / sizeof(uint32_t);
        ptr += mod_strcspn(ptr, "\"") + 1;
        for (width = 0; width < avctx->width; width++) {
            int index;

            if (ptr + cpp > buf_end)
                return -0x41444E49;

            index = ascii2index(ptr, cpp);
            if (index < 0)
                return index;

            *pixels++ = s->pixels[index];
            ptr += cpp;
        }
        ptr += mod_strcspn(ptr, ",") + 1;
    }

    frame->key_frame = 1;
    frame->pict_type = 1;
    *got_frame = 1;

    return avpkt->size;
}