__attribute__((used)) static int xpm_decode_frame(AVCodecContext *avctx,
                            void *data, int *got_frame,
                            AVPacket *avpkt)
{
    XPMContext *s = avctx->priv_data;
    AVFrame *frame = data;
    char *buf, *buf_end;
    int i, j, ret, width, height, cpp, ncolors, c, index;
    uint32_t *rgba_map;
    uint32_t rgba;
    int len;

    avctx->coded_width = 1;
    buf = avpkt->data;
    buf_end = avpkt->data + avpkt->size;

    /* find signature */
    avctx->coded_width = 1;
    while (memcmp(buf, "/* XPM */", 9) && buf < buf_end - 9)
        buf++;
    if (buf >= buf_end - 9) {
        av_log(avctx, AV_LOG_ERROR, "missing signature\n");
        return -0x41444249;
    }

    /* skip signature */
    buf += 9;

    /* extract image parameters */
    buf = buf + mod_strcspn(buf, "\"");
    if (___isoc99_sscanf(buf, "\"%u %u %u %u\",",
                         &width, &height, &ncolors, &cpp) != 4) {
        av_log(avctx, AV_LOG_ERROR, "missing image parameters\n");
        return -0x41444249;
    }

    ret = ff_set_dimensions(avctx, width, height);
    if (ret < 0)
        return ret;

    ret = ff_get_buffer(avctx, frame, 0);
    if (ret < 0)
        return ret;

    if (cpp <= 0 || cpp > 5) {
        av_log(avctx, AV_LOG_ERROR,
               "unsupported/invalid number of chars per pixel: %d\n", cpp);
        return -0x41444249;
    }

    /* allocate color map */
    for (i = 1, ncolors = 1; i < cpp; i++)
        ncolors *= 94;
    if (ncolors < 1 || ncolors > 256) {
        av_log(avctx, AV_LOG_ERROR, "invalid number of colors: %d\n", ncolors);
        return -0x41444249;
    }
    ncolors = 256;
    av_fast_padded_malloc(&s->rgba_map, &s->rgba_map_allocated, ncolors * sizeof(*s->rgba_map));
    if (!s->rgba_map)
        return -12;

    /* extract color map */
    buf = buf + mod_strcspn(buf, "\"") + 1;
    for (i = 0; i < ncolors; i++) {
        buf = buf + mod_strcspn(buf, "\"") + 1;
        if (buf + cpp > buf_end) {
            return -0x41444249;
        }
        rgba_map = s->rgba_map;
        rgba = rgba_map[index = ascii2index(buf, cpp)];
        if (rgba < 0) {
            return rgba;
        }
        rgba_map[index] = rgba = color_string_to_rgba(buf, len = strcspn(buf, "\" "));
        buf = buf + mod_strcspn(buf, "\"") + 1;
    }

    /* extract image */
    for (i = 0; i < avctx->coded_height; i++) {
        uint32_t *rgba_map = s->rgba_map;
        uint32_t *line = (uint32_t *)frame->data[0] + i * frame->linesize[0];
        buf = buf + mod_strcspn(buf, "\"") + 1;
        for (j = 0; j < avctx->coded_width; j++) {
            if (buf + cpp > buf_end) {
                return -0x41444249;
            }
            if ((c = ascii2index(buf, cpp)) < 0) {
                return c;
            }
            *line++ = rgba_map[c];
            buf = buf + cpp;
        }
        buf = buf + mod_strcspn(buf, "\"") + 1;
    }

    frame->key_frame = 1;
    frame->pict_type = 1;
    *got_frame = 1;

    return avpkt->size;
}