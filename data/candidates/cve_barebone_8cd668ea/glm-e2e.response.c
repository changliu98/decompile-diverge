void png_check_chunk_length(struct png_struct_def *png_ptr, uint32_t length) {
    uint64_t limit = 0x7fffffff;

    if (png_ptr->unknown_0 > 0 && png_ptr->unknown_0 < limit) {
        limit = png_ptr->unknown_0;
    }

    if (png_ptr->chunk_name == 0x49444154) { // "IDAT"
        uint64_t total_size = 0x7fffffff;
        uint64_t pixel_size = png_ptr->width * png_ptr->bit_depth;
        
        uint32_t channels = 1;
        if (png_ptr->color_type > 8) {
            channels = 2;
        }
        pixel_size *= channels;
        pixel_size += 1;
        
        uint32_t extra = 0;
        if (png_ptr->color_type != 0) {
            extra = 6;
        }
        pixel_size += extra;
        
        uint64_t row_size = png_ptr->height * pixel_size;
        
        if (row_size > 0xffffffff / pixel_size) {
            total_size = 0x7fffffff;
        } else {
            total_size = png_ptr->height * pixel_size;
        }
        
        if (pixel_size > 0x7f36) {
            pixel_size = 0x7f36;
        }
        
        total_size = total_size / pixel_size * 5 + 6 + total_size;
        
        if (total_size >= 0x7fffffff) {
            total_size = 0x7fffffff;
        }
        
        if (limit < total_size) {
            limit = total_size;
        }
    }

    if (length > limit) {
        png_chunk_error(png_ptr, "chunk length too large");
    }
}