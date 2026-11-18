void process_bitmap_updates(uint8_t **s) {
    uint16_t num_updates;
    uint16_t left, top, right, bottom, width, height, bpp;
    uint16_t bytes_per_row, dummy1, dummy2;
    uint16_t update_width, update_height;
    uint16_t flags, compressed_size;
    uint8_t *compressed_data;
    uint8_t *bitmap_data;
    int i;
    int y;

    logger(4, 0, "process_bitmap_updates\n");
    
    num_updates = *(uint16_t *)*s;
    *s += 2;
    
    for (i = 0; i < num_updates; i++) {
        left = *(uint16_t *)*s;
        *s += 2;
        top = *(uint16_t *)*s;
        *s += 2;
        right = *(uint16_t *)*s;
        *s += 2;
        bottom = *(uint16_t *)*s;
        *s += 2;
        width = *(uint16_t *)*s;
        *s += 2;
        height = *(uint16_t *)*s;
        *s += 2;
        bpp = *(uint16_t *)*s;
        *s += 2;
        
        bytes_per_row = (bpp + 7) / 8;
        
        dummy1 = *(uint16_t *)*s;
        *s += 2;
        dummy2 = *(uint16_t *)*s;
        *s += 2;
        
        update_width = right - left + 1;
        update_height = bottom - top + 1;
        
        logger(5, 0, "l=%d t=%d r=%d b=%d w=%d h=%d bpp=%d\n", left, top, right, bottom, width, height, bpp);
        
        if (dummy1 == 0) {
            bitmap_data = xmalloc((unsigned long)width * height * bytes_per_row);
            
            for (y = 0; y < height; y++) {
                memcpy(bitmap_data + (height - y - 1) * width * bytes_per_row, *s, width * bytes_per_row);
                *s += width * bytes_per_row;
            }
            
            ui_paint_bitmap(left, top, update_width, update_height, width, height, bitmap_data);
            xfree(bitmap_data);
        } else {
            if (dummy1 & 0x400) {
                compressed_size = dummy2;
            } else {
                compressed_size = *(uint16_t *)*s;
                *s += 2;
                *s += 4;
            }
            
            compressed_data = *s;
            *s += compressed_size;
            
            bitmap_data = xmalloc((unsigned long)width * height * bytes_per_row);
            
            if (bitmap_decompress(bitmap_data, width, height, compressed_data, compressed_size, bytes_per_row)) {
                ui_paint_bitmap(left, top, update_width, update_height, width, height, bitmap_data);
            } else {
                logger(5, 2, "Failed to decompress bitmap\n");
            }
            
            xfree(bitmap_data);
        }
    }
}