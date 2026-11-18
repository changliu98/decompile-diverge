static drmp3_bool32 drmp3__on_seek_64(drmp3* pMP3, drmp3_uint64 offset, drmp3_seek_origin origin)
{
    if (offset <= 0x7FFFFFFF) {
        return drmp3__on_seek(pMP3, (int)offset, origin);
    }

    /* Getting here "offset" is too large for a 32-bit integer. We just keep seeking forward until we hit the offset. */
    if (!drmp3__on_seek(pMP3, 0x7FFFFFFF, DRMP3_SEEK_SET)) {
        return DRMP3_FALSE;
    }

    offset -= 0x7FFFFFFF;
    while (offset > 0) {
        if (offset <= 0x7FFFFFFF) {
            if (!drmp3__on_seek(pMP3, (int)offset, DRMP3_SEEK_CUR)) {
                return DRMP3_FALSE;
            }
            offset = 0;
        } else {
            if (!drmp3__on_seek(pMP3, 0x7FFFFFFF, DRMP3_SEEK_CUR)) {
                return DRMP3_FALSE;
            }
            offset -= 0x7FFFFFFF;
        }
    }

    return DRMP3_TRUE;
}