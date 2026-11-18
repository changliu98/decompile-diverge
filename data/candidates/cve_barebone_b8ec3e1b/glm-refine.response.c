int pict_type

int __cdecl xpm_decode_frame(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt)
{
    XPMDecContext *x = (XPMDecContext *)avctx->priv_data;
    AVFrame *frame = (AVFrame *)data;
    const uint8_t *ptr = avpkt->data;
    const uint8_t *end = avpkt->data + avpkt->size;
    
    int len, cpp, ncolors;
    int64_t size;
    int i, j, ret;
    const uint8_t *index;
    uint32_t *dst;
    
    avctx->pix_fmt = AV_PIX_FMT_RGBA; // 1
    
    // Find the XPM signature "/* XPM */"
    while (memcmp(ptr, "/* XPM */", 9) != 0) {
        if (ptr >= end - 9)
            goto missing_signature;
        ptr++;
    }
    
    if (ptr >= end)
        goto missing_signature;
    
    // Skip to the first quote and parse the header
    ptr += mod_strcspn((const char *)ptr, "\"");
    if (sscanf((const char *)ptr, "\"%d %d %d %d\"", &avctx->width, &avctx->height, &ncolors, &cpp) != 4) {
        av_log(avctx, AV_LOG_ERROR, "missing image parameters\n");
        return AVERROR_INVALIDDATA;
    }
    
    if ((ret = ff_set_dimensions(avctx, avctx->width, avctx->height)) < 0)
        return ret;
        
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
        
    if (cpp <= 0 || cpp >= 5) {
        av_log(avctx, AV_LOG_ERROR, "unsupported/invalid number of chars per pixel: %d\n", cpp);
        return AVERROR_INVALIDDATA;
    }
    
    // Maximum unique characters per pixel (printable ASCII: 94 chars)
    size = 1;
    for (i = 0; i < cpp; i++)
        size *= 94;
        
    if (ncolors <= 0 || ncolors > size) {
        av_log(avctx, AV_LOG_ERROR, "invalid number of colors: %d\n", ncolors);
        return AVERROR_INVALIDDATA;
    }
    
    av_fast_padded_malloc(x, &x->pixels_size, 4 * size);
    if (!x->pixels)
        return AVERROR(ENOMEM);
        
    // Parse color palette
    ptr += mod_strcspn((const char *)ptr, ",") + 1;
    for (i = 0; i < ncolors; i++) {
        ptr += mod_strcspn((const char *)ptr, "\"") + 1;
        if (ptr + cpp > end)
            return AVERROR_INVALIDDATA;
            
        index = ptr;
        char *color_key = strstr((const char *)ptr + cpp, "c ");
        if (!color_key)
            return AVERROR_INVALIDDATA;
            
        const char *color_str = color_key + 2;
        len = strcspn(color_str, "\" ");
        
        ret = ascii2index(index, cpp);
        if (ret < 0)
            return ret;
            
        x->pixels[ret] = color_string_to_rgba(color_str, len);
        ptr += mod_strcspn((const char *)color_str, ",") + 1;
    }
    
    // Parse pixel data
    for (i = 0; i < avctx->height; i++) {
        dst = (uint32_t *)(frame->data[0] + frame->linesize[0] * i);
        ptr += mod_strcspn((const char *)ptr, "\"") + 1;
        
        for (j = 0; j < avctx->width; j++) {
            if (ptr + cpp > end)
                return AVERROR_INVALIDDATA;
                
            ret = ascii2index(ptr, cpp);
            if (ret < 0)
                return ret;
                
            *dst++ = x->pixels[ret];
            ptr += cpp;
        }
        ptr += mod_strcspn((const char *)ptr, ",") + 1;
    }
    
    frame->key_frame = 1; // AV_PICTURE_TYPE_I = 1
    frame->pict_type = AV_PICTURE_TYPE_I;
    *got_frame = 1;
    
    return avpkt->size;

missing_signature:
    av_log(avctx, AV_LOG_ERROR, "missing signature\n");
    return AVERROR_INVALIDDATA;
}