The decompiled function
int drflac__seek_to_byte(drflac* pFlac, int64_t offset) {
    // The compiler optimized away the string literals, but the line numbers 
    // 0xb41 and 0xb42 correspond to standard dr_flac assertions.
    // assert(pFlac != NULL);
    // assert(offset > 0);

    if (offset <= 0x7FFFFFFF) {
        // If the offset fits in a 32-bit signed integer, seek directly
        if (!pFlac->seek(pFlac->pUserData, (int)offset, 0)) { // SEEK_SET = 0
            return 0;
        }
    } else {
        // For offsets larger than 2GB, seek in 2GB chunks to bypass 
        // 32-bit `long` limitations on platforms where long is 32-bit.
        int64_t bytesRemaining = offset;
        
        while (bytesRemaining > 0x7FFFFFFF) {
            // Seek forward by 2GB (0x7FFFFFFF)
            if (!pFlac->seek(pFlac->pUserData, 0x7FFFFFFF, 1)) { // SEEK_CUR = 1
                return 0;
            }
            bytesRemaining -= 0x7FFFFFFF;
        }
        
        // Seek by whatever is remaining (guaranteed to be <= 2GB)
        if (bytesRemaining > 0) {
            if (!pFlac->seek(pFlac->pUserData, (int)bytesRemaining, 1)) { // SEEK_CUR = 1
                return 0;
            }
        }
    }

    // Flush/Reset the internal decoder buffer state after the raw byte seek
    drflac__reset_decoder(pFlac);
    
    return 1;
}