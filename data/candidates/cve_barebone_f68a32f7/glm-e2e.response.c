int resize_vbar_entry(void* context, struct vbar_entry* entry) {
    int bpp;
    int old_size;
    int diff_size;
    void* new_data;
    int ret;

    if (entry->height > entry->width) {
        bpp = FreeRDPGetBytesPerPixel(*(int*)((char*)context + 0x30));
        old_size = entry->width * bpp;
        diff_size = (entry->height - entry->width) * bpp;
        
        entry->width = entry->height;
        
        new_data = winpr_aligned_recalloc(entry->data, entry->height, bpp, 0x20);
        if (!new_data) {
            return 0;
        }
        
        memset((char*)new_data + old_size, 0, diff_size);
        entry->data = new_data;
    }
    
    if (!entry->data && entry->width != 0) {
        return 0;
    }
    
    return 1;
}