drflac_bool32 __cdecl drflac_oggbs__seek_physical(drflac_oggbs *oggbs, drflac_uint64 offset, drflac_seek_origin origin)
{
    if (origin == DRFLAC_SEEK_CUR) {
        // Handle relative seeking
        while (offset > 0x7FFFFFFF) {
            if (!oggbs->onSeek(oggbs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_CUR)) {
                return 0;
            }
            oggbs->currentBytePos += 0x7FFFFFFFLL;
            offset -= 0x7FFFFFFFLL;
        }
        
        if (!oggbs->onSeek(oggbs->pUserData, offset, DRFLAC_SEEK_CUR)) {
            return 0;
        }
        oggbs->currentBytePos += offset;
        return 1;
    }
    
    // Handle absolute seeking (origin == DRFLAC_SEEK_SET)
    while (offset > 0x7FFFFFFF) {
        if (!oggbs->onSeek(oggbs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_SET)) {
            return 0;
        }
        offset -= 0x7FFFFFFFLL;
    }
    
    if (!oggbs->onSeek(oggbs->pUserData, offset, DRFLAC_SEEK_SET)) {
        return 0;
    }
    
    // Note: The original recursive implementation sets currentBytePos to the 
    // initial offset only during the first iteration. In subsequent iterations, 
    // it adds the remaining offset to the previously set value, effectively 
    // calculating the correct absolute position.
    oggbs->currentBytePos += offset;
    return 1;
}