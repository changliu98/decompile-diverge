0xBEBBB1B7

int xpm_decode_frame(AVCodecContext *avctx, AVFrame *p_frame,
                     int *got_frame, AVPacket *avpkt)
{
    XPMContext *x = &avctx->priv;
    AVFrame *frame = p_frame;
    const uint8_t *buf = avpkt->data;
    const uint8_t *end = avpkt->data + avpkt->size;
    const uint8_t *ptr;
    int ret;
    int ncolors, cpp;
    int size;
    int i, j;

    avctx->width = 1; // Set a default width

    // Find the first quote
    ptr = buf;
    while (ptr < end) {
        if (memcmp(ptr, "\"", 1) == 0)
            break;
        if (ptr + 9 > end)
            break;
        ptr++;
    }

    if (ptr >= end) {
        av_log(avctx, AV_LOG_ERROR, "Missing header\n");
        return AVERROR_INVALIDDATA;
    }

    ptr += mod_strcspn(ptr, "\"");
    
    // Parse header: width, height, ncolors, chars_per_pixel
    if (sscanf(ptr, "\"%u %u %u %u\"", &avctx->width, &avctx->height, &ncolors, &cpp) != 4) {
        av_log(avctx, AV_LOG_ERROR, "Missing width/height\n");
        return AVERROR_INVALIDDATA;
    }

    // Set dimensions
    ret = ff_set_dimensions(avctx, avctx->width, avctx->height);
    if (ret < 0)
        return ret;

    // Get frame buffer
    ret = ff_get_buffer(avctx, frame, 0);
    if (ret < 0)
        return ret;

    // Validate chars per pixel
    if (cpp <= 0 || cpp >= 5) {
        av_log(avctx, AV_LOG_ERROR, "Unsupported chars per pixel: %d\n", cpp);
        return AVERROR_INVALIDDATA;
    }

    // Calculate hash size
    size = 1;
    for (i = 0; i < cpp; i++)
        size *= 94; // 0x5E

    // Validate ncolors
    if (ncolors <= 0 || (int64_t)ncolors > size) {
        av_log(avctx, AV_LOG_ERROR, "Too many colors: %d\n", ncolors);
        return AVERROR_INVALIDDATA;
    }

    size *= 4; // Size in bytes for uint32_t array

    // Allocate pixel map
    av_fast_padded_malloc(x, &x->buf, size);
    if (!x->pixels)
        return -12; // AVERROR(ENOMEM)

    // Skip to next line
    ptr += mod_strcspn(ptr, ",") + 1;

    // Parse colors
    for (i = 0; i < ncolors; i++) {
        ptr += mod_strcspn(ptr, "\"") + 1;
        if (ptr + cpp > end)
            return AVERROR_INVALIDDATA;

        const uint8_t *start = ptr;
        ptr += cpp;

        ptr = strstr(ptr, "c ");
        if (!ptr)
            return AVERROR_INVALIDDATA;
        ptr += 2;

        int len = strcspn(ptr, "\"");
        int index = ascii2index(start, cpp);
        if (index < 0)
            return index;

        x->pixels[index] = color_string_to_rgba(ptr, len);

        ptr += mod_strcspn(ptr, ",") + 1;
    }

    // Decode pixel data
    for (i = 0; i < avctx->height; i++) {
        uint32_t *dst = (uint32_t *)(frame->data[0] + i * frame->linesize[0]);
        ptr += mod_strcspn(ptr, "\"") + 1;

        for (j = 0; j < avctx->width; j++) {
            if (ptr + cpp > end)
                return AVERROR_INVALIDDATA;

            int index = ascii2index(ptr, cpp);
            if (index < 0)
                return index;

            *dst++ = x->pixels[index];
            ptr += cpp;
        }

        ptr += mod_strcspn(ptr, ",") + 1;
    }

    frame->key_frame = 1;
    frame->pict_type = 1; // AV_PICTURE_TYPE_I
    *got_frame = 1;

    return avpkt->size;
}