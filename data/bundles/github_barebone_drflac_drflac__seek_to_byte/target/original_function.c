static drflac_bool32 drflac__seek_to_byte(drflac_bs* bs, drflac_uint64 offsetFromStart)
{
    DRFLAC_ASSERT(bs != NULL);
    DRFLAC_ASSERT(offsetFromStart > 0);

    /*
    Seeking from the start is not quite as trivial as it sounds because the onSeek callback takes a signed 32-bit integer (which
    is intentional because it simplifies the implementation of the onSeek callbacks), however offsetFromStart is unsigned 64-bit.
    To resolve we just need to do an initial seek from the start, and then a series of offset seeks to make up the remainder.
    */
    if (offsetFromStart > 0x7FFFFFFF) {
        drflac_uint64 bytesRemaining = offsetFromStart;
        if (!bs->onSeek(bs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_SET)) {
            return DRFLAC_FALSE;
        }
        bytesRemaining -= 0x7FFFFFFF;

        while (bytesRemaining > 0x7FFFFFFF) {
            if (!bs->onSeek(bs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_CUR)) {
                return DRFLAC_FALSE;
            }
            bytesRemaining -= 0x7FFFFFFF;
        }

        if (bytesRemaining > 0) {
            if (!bs->onSeek(bs->pUserData, (int)bytesRemaining, DRFLAC_SEEK_CUR)) {
                return DRFLAC_FALSE;
            }
        }
    } else {
        if (!bs->onSeek(bs->pUserData, (int)offsetFromStart, DRFLAC_SEEK_SET)) {
            return DRFLAC_FALSE;
        }
    }

    /* The cache should be reset to force a reload of fresh data from the client. */
    drflac__reset_cache(bs);
    return DRFLAC_TRUE;
}