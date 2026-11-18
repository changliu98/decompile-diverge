drflac_bool32 __cdecl drflac__seek_to_byte(drflac_bs *bs, drflac_uint64 offsetFromStart)
{
    drflac_uint64 bytesRemaining;

    // Asserts for null pointer and invalid offset
    if (!bs)
        _assert_fail("bs != ((void*)0)", "func.c", 0xB41u, "drflac_bool32 drflac__seek_to_byte(drflac_bs *, drflac_uint64)");
    if (!offsetFromStart)
        _assert_fail("offsetFromStart > 0", "func.c", 0xB42u, "drflac_bool32 drflac__seek_to_byte(drflac_bs *, drflac_uint64)");

    // If the offset fits in a 32-bit signed integer, seek directly from the start
    if (offsetFromStart <= 0x7FFFFFFF) {
        if (!bs->onSeek(bs->pUserData, offsetFromStart, DRFLAC_SEEK_SET))
            return 0;
    } 
    // Otherwise, chunk the seeks to avoid 32-bit integer overflow on systems that limit seek offsets
    else {
        // Initial seek to the maximum 32-bit signed integer value
        if (!bs->onSeek(bs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_SET))
            return 0;

        // Seek the remaining distance in chunks of 0x7FFFFFFF
        bytesRemaining = offsetFromStart - 0x7FFFFFFF;
        while (bytesRemaining > 0x7FFFFFFF) {
            if (!bs->onSeek(bs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_CUR))
                return 0;
            bytesRemaining -= 0x7FFFFFFFLL;
        }

        // Seek any final remaining bytes
        if (bytesRemaining && !bs->onSeek(bs->pUserData, bytesRemaining, DRFLAC_SEEK_CUR))
            return 0;
    }

    // Reset the bitstream cache after a successful seek
    drflac__reset_cache(bs);
    return 1;
}