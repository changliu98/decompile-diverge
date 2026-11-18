int drmp3__on_seek_64(void* pUserData, uint64_t offset, int origin) {
    int result;
    
    // If the offset fits in a 32-bit integer, just do a single 32-bit seek
    if (offset <= 0x7fffffff) {
        result = drmp3__on_seek(pUserData, (uint32_t)offset, origin);
        return result;
    }
    
    // Otherwise, seek by 2GB (0x7fffffff) chunks
    if (!drmp3__on_seek(pUserData, 0x7fffffff, 0)) {
        return 0;
    }
    
    offset -= 0x7fffffff;
    
    // Loop to seek the remaining distance in 2GB chunks
    while (offset > 0) {
        if (offset <= 0x7fffffff) {
            // Seek the remaining amount
            if (!drmp3__on_seek(pUserData, (uint32_t)offset, 1)) {
                return 0;
            }
            offset = 0;
        } else {
            // Seek another 2GB chunk
            if (!drmp3__on_seek(pUserData, 0x7fffffff, 1)) {
                return 0;
            }
            offset -= 0x7fffffff;
        }
    }
    
    return 1;
}