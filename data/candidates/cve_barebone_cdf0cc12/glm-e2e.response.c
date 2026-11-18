bitmap_update* update_read_bitmap_update(update_context *ctx, void *stream) {
    bitmap_update *bu;
    unsigned int i;
    unsigned short new_capacity;
    void *new_rects;

    // Allocate the bitmap_update structure (size 0x18 = 24 bytes)
    bu = calloc(1, 0x18);
    if (!bu)
        return NULL;

    // Check if stream has at least 2 bytes remaining
    if (Stream_GetRemainingLength(stream) < 2) {
        free_bitmap_update(ctx, bu);
        return NULL;
    }

    // Read 16-bit little-endian integer from stream
    bu->numUpdates = *(unsigned char *)stream | (*(unsigned char *)(stream + 1) << 8);
    Stream_Seek(stream, 2);

    // If the number of updates exceeds the current capacity, expand the array
    if (bu->numUpdates > bu->count) {
        new_capacity = bu->numUpdates * 2;
        new_rects = realloc(bu->rectangles, (size_t)new_capacity * 0x48);
        if (!new_rects) {
            free_bitmap_update(ctx, bu);
            return NULL;
        }
        bu->rectangles = new_rects;
        
        // Zero out the newly allocated memory
        memset((char *)bu->rectangles + (size_t)bu->count * 0x48, 0, (size_t)(new_capacity - bu->count) * 0x48);
        bu->count = new_capacity;
    }

    // Iterate over the number of updates and read bitmap data
    for (i = 0; i < bu->numUpdates; i++) {
        if (!update_read_bitmap_data(ctx, stream, (char *)bu->rectangles + (size_t)i * 0x48)) {
            free_bitmap_update(ctx, bu);
            return NULL;
        }
    }

    return bu;
}