void WritePixels(struct Context *ctx, struct Output *out, unsigned char *src, unsigned short count) {
    struct GifInfo *gif = ctx->gif;
    while (count > 0) {
        unsigned short write_count = (out->width < count) ? out->width : count;
        
        if ((ctx->flags >> 4) & 1) {
            if (gif->flags & 1) {
                memcpy(out->ptr, src, write_count);
                src += write_count;
                out->ptr += write_count;
            } else {
                for (int i = 0; i < write_count; i++) {
                    unsigned int color = GifIndexToTrueColor(ctx->palette, *src++);
                    *out->ptr = color;
                    out->ptr += 4;
                }
            }
        } else {
            if (gif->flags & 1) {
                for (int i = 0; i < write_count; i++) {
                    if (*src != ctx->transparent_index) {
                        *out->ptr = *src;
                    }
                    src++;
                    out->ptr++;
                }
            } else {
                for (int i = 0; i < write_count; i++) {
                    if (*src != ctx->transparent_index) {
                        unsigned int color = GifIndexToTrueColor(ctx->palette, *src);
                        *out->ptr = color;
                    }
                    src++;
                    out->ptr += 4;
                }
            }
        }
        
        out->width -= write_count;
        if (out->width == 0) {
            out->width = ctx->height;
            switch (out->interlace_step) {
                case 0:
                    out->y += 1;
                    break;
                case 1:
                    out->y += 8;
                    if (out->y >= gif->height) {
                        out->interlace_step++;
                        out->y = ctx->start_y + 4;
                    }
                    break;
                case 2:
                    out->y += 8;
                    if (out->y >= gif->height) {
                        out->interlace_step++;
                        out->y = ctx->start_y + 2;
                    }
                    break;
                case 3:
                    out->y += 4;
                    if (out->y >= gif->height) {
                        out->interlace_step++;
                        out->y = ctx->start_y + 1;
                    }
                    break;
                default:
                    out->y += 2;
                    break;
            }
            
            if (gif->flags & 1) {
                out->ptr = gif->frame_buffer + (out->y * gif->stride) + ctx->start_x;
            } else {
                out->ptr = gif->frame_buffer + (out->y * gif->stride + ctx->start_x) * 4;
            }
        }
        count -= write_count;
    }
}