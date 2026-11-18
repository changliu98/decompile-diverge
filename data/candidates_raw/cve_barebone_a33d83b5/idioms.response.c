void process_bitmap_updates(struct stream *stream)
{
    int i;
    int num_updates;
    int left; int right; int top; int bottom;
    int width; int height;
    int bpp; int Bpp; int compress; int bufsize;
    int cx; int cy;
    unsigned char *data; unsigned char *buf;
    logger(log_subject_t::Protocol, log_level_t::Debug, "%s()", "process_bitmap_updates");
    num_updates = (stream->p)[0] | ((stream->p)[1] << 8);
    stream->p += 2;
    for (i = 0; i < num_updates; i++) {
        left = (stream->p)[0] | ((stream->p)[1] << 8);
        stream->p += 2;
        top = (stream->p)[0] | ((stream->p)[1] << 8);
        stream->p += 2;
        right = (stream->p)[0] | ((stream->p)[1] << 8);
        stream->p += 2;
        bottom = (stream->p)[0] | ((stream->p)[1] << 8);
        stream->p += 2;
        width = (stream->p)[0] | ((stream->p)[1] << 8);
        stream->p += 2;
        height = (stream->p)[0] | ((stream->p)[1] << 8);
        stream->p += 2;
        bpp = (stream->p)[0] | ((stream->p)[1] << 8);
        stream->p += 2;
        Bpp = (bpp + 7)/8;
        compress = (stream->p)[0] | ((stream->p)[1] << 8);
        stream->p += 2;
        bufsize = (stream->p)[0] | ((stream->p)[1] << 8);
        stream->p += 2;
        cx = right - left + 1;
        cy = bottom - top + 1;
        logger(log_subject_t::Graphics, log_level_t::Debug, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d",
            left, top, right, bottom, width, height, bpp, compress);
        if (compress == 0) {
            buf = (unsigned char *)malloc(width * height * Bpp);
            int y;
            for (y = 0; y < height; y++) {
                read_line(&buf[(height - y - 1)*width * Bpp], stream->p, width * Bpp);
                stream->p += width * Bpp;
            }
            draw_bitmap(left, top, cx, cy, width, height, buf);
            free(buf);
        }
        else if (compress & 0x400) {
            int size = bufsize;
            data = stream->p;
            stream->p += size;
            buf = (unsigned char *)malloc(width * height * Bpp);
            if (decompress(buf, width, height, data, size, Bpp)) {
                draw_bitmap(left, top, cx, cy, width, height, buf);
            }
            else {
                log_print(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
            }
            free(buf);
        }
        else {
            int size = (stream->p)[0] | ((stream->p)[1] << 8);
            stream->p += 2;
            data = stream->p;
            stream->p += size;
            stream->p += 2;
            stream->p += 2;
            buf = (unsigned char *)malloc(width * height * Bpp);
            if (decompress(buf, width, height, data, size, Bpp)) {
                draw_bitmap(left, top, cx, cy, width, height, buf);
            }
            else {
                log_print(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
            }
            free(buf);
        }
    }
}