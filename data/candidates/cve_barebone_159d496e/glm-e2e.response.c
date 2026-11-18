void process_bitmap_updates(STREAM *s) {
    logger(4, 0, "Processing bitmap updates");
    
    uint16_t num_updates = *(uint16_t *)s->p;
    s->p += 2;
    
    for (int i = 0; i < num_updates; i++) {
        uint16_t left = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t top = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t right = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t bottom = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t width = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t height = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t bpp = *(uint16_t *)s->p;
        s->p += 2;
        
        uint16_t bytes_per_row = (bpp + 7) / 8;
        
        uint16_t flags = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t compressed_size = *(uint16_t *)s->p;
        s->p += 2;
        
        uint16_t bmp_width = right - left + 1;
        uint16_t bmp_height = bottom - top + 1;
        
        logger(5, 0, "Bitmap: left=%d top=%d right=%d bottom=%d width=%d height=%d bpp=%d", 
               left, top, right, bottom, width, height, bpp);
        
        uint8_t *data = NULL;
        
        if (flags == 0) {
            // Uncompressed bitmap
            data = xmalloc((unsigned long)width * height * bytes_per_row);
            
            for (int y = 0; y < height; y++) {
                uint8_t *dst = data + (unsigned long)(height - y - 1) * width * bytes_per_row;
                memcpy(dst, s->p, (unsigned long)width * bytes_per_row);
                s->p += (unsigned long)width * bytes_per_row;
            }
            
            ui_paint_bitmap(left, top, bmp_width, bmp_height, width, height, data);
            xfree(data);
        } else {
            // Compressed bitmap
            uint16_t actual_compressed_size;
            
            if (flags & 0x400) {
                actual_compressed_size = compressed_size;
            } else {
                actual_compressed_size = *(uint16_t *)s->p;
                s->p += 2;
                s->p += 4; // Skip 4 bytes of padding/unknown data
            }
            
            uint8_t *compressed_data = s->p;
            s->p += actual_compressed_size;
            
            data = xmalloc((unsigned long)width * height * bytes_per_row);
            
            if (bitmap_decompress(data, width, height, compressed_data, actual_compressed_size, bytes_per_row)) {
                ui_paint_bitmap(left, top, bmp_width, bmp_height, width, height, data);
            } else {
                logger(5, 2, "Failed to decompress bitmap");
            }
            
            xfree(data);
        }
    }
}