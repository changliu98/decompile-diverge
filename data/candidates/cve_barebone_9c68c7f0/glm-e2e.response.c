void WritePixels(struct GifFileType *gif, struct SavedImage *frame, unsigned char *buffer, unsigned short len) {
    while (len > 0) {
        unsigned short count = frame->width < len ? frame->width : len;
        unsigned char *pixels = gif->SavedImages; // offset 0x8 from gif
        
        if ((gif->some_byte >> 4) & 1) { // offset 0x1b
            if (pixels[0x43] & 1) {
                for (int i = 0; i < count; i++) {
                    if (*buffer != gif->transparent_color) { // offset 0x1a
                        *frame->data = *buffer;
                    }
                    buffer++;
                    frame->data++;
                }
            } else {
                for (int i = 0; i < count; i++) {
                    if (*buffer != gif->transparent_color) {
                        *(unsigned int *)frame->data = GifIndexToTrueColor(gif, *buffer);
                    }
                    buffer++;
                    frame->data += 4;
                }
            }
        } else {
            if (pixels[0x43] & 1) {
                memcpy(frame->data, buffer, count);
                buffer += count;
                frame->data += count;
            } else {
                for (int i = 0; i < count; i++) {
                    unsigned char c = *buffer++;
                    *(unsigned int *)frame->data = GifIndexToTrueColor(gif, c);
                    frame->data += 4;
                }
            }
        }
        
        frame->width -= count;
        
        if (frame->width == 0) {
            frame->width = gif->image_width; // offset 0x1e
            
            switch (frame->interlace) { // offset 0x18
                case 0:
                    frame->y += 8;
                    if (frame->y >= pixels->height) { // offset 0x3c
                        frame->interlace++;
                        frame->y = gif->width + 4; // offset 0x24
                    }
                    break;
                case 1:
                    frame->y += 8;
                    if (frame->y >= pixels->height) {
                        frame->interlace++;
                        frame->y = gif->width + 2;
                    }
                    break;
                case 2:
                    frame->y += 4;
                    if (frame->y >= pixels->height) {
                        frame->interlace++;
                        frame->y = gif->width + 1;
                    }
                    break;
                case 3:
                    frame->y += 2;
                    break;
                default:
                    break;
            }
            
            if (pixels[0x43] & 1) {
                frame->data = pixels->raster_bits + (frame->y * pixels->width) + gif->left; // offset 0x20, 0x3a, 0x22
            } else {
                frame->data = pixels->raster_bits + (frame->y * pixels->width + gif->left) * 4;
            }
        }
        
        len -= count;
    }
}