Function signature inferred from the recursive call and callback usage
int drflac_oggbs__seek_physical(drflac_oggbs* pOGGBS, uint64_t offset, int origin) {
    int result;

    if (origin == 0) { // Seek from beginning (SEEK_SET)
        if (offset <= 0x7FFFFFFF) {
            // Direct seek
            if (!pOGGBS->onSeek(pOGGBS->pUserData, (int)offset, 0)) {
                result = 0;
            } else {
                pOGGBS->currentPos = offset;
                result = 1;
            }
        } else {
            // Offset exceeds 32-bit int max, seek to max first
            if (!pOGGBS->onSeek(pOGGBS->pUserData, 0x7FFFFFFF, 0)) {
                result = 0;
            } else {
                pOGGBS->currentPos = offset;
                // Recursively seek the remaining bytes from the current position
                result = drflac_oggbs__seek_physical(pOGGBS, offset - 0x7FFFFFFF, 1);
            }
        }
    } else { // origin != 0, Seek from current position (SEEK_CUR)
        // Loop to consume the offset in 0x7FFFFFFF chunks
        while (offset > 0x7FFFFFFF) {
            if (!pOGGBS->onSeek(pOGGBS->pUserData, 0x7FFFFFFF, 1)) {
                return 0;
            }
            pOGGBS->currentPos += 0x7FFFFFFF;
            offset -= 0x7FFFFFFF;
        }
        
        // Seek the remaining offset
        if (!pOGGBS->onSeek(pOGGBS->pUserData, (int)offset, 1)) {
            result = 0;
        } else {
            pOGGBS->currentPos += offset;
            result = 1;
        }
    }

    return result;
}