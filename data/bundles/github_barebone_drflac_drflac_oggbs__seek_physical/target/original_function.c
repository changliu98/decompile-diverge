static drflac_bool32 drflac_oggbs__seek_physical(drflac_oggbs* oggbs, drflac_uint64 offset, drflac_seek_origin origin)
{
    if (origin == DRFLAC_SEEK_SET) {
        if (offset <= 0x7FFFFFFF) {
            if (!oggbs->onSeek(oggbs->pUserData, (int)offset, DRFLAC_SEEK_SET)) {
                return DRFLAC_FALSE;
            }
            oggbs->currentBytePos = offset;

            return DRFLAC_TRUE;
        } else {
            if (!oggbs->onSeek(oggbs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_SET)) {
                return DRFLAC_FALSE;
            }
            oggbs->currentBytePos = offset;

            return drflac_oggbs__seek_physical(oggbs, offset - 0x7FFFFFFF, DRFLAC_SEEK_CUR);
        }
    } else {
        while (offset > 0x7FFFFFFF) {
            if (!oggbs->onSeek(oggbs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_CUR)) {
                return DRFLAC_FALSE;
            }
            oggbs->currentBytePos += 0x7FFFFFFF;
            offset -= 0x7FFFFFFF;
        }

        if (!oggbs->onSeek(oggbs->pUserData, (int)offset, DRFLAC_SEEK_CUR)) {    /* <-- Safe cast thanks to the loop above. */
            return DRFLAC_FALSE;
        }
        oggbs->currentBytePos += offset;

        return DRFLAC_TRUE;
    }
}