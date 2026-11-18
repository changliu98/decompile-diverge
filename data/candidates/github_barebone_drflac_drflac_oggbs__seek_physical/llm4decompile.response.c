drflac_bool32 drflac_oggbs__seek_physical(drflac_oggbs *oggbs, drflac_uint64 offset, drflac_seek_origin origin)
{
    if (origin == DRFLAC_SEEK_SET) {
        if (offset < 0x80000000) {
            if (!oggbs->onSeek(oggbs->pUserData, (drflac_int64)offset, DRFLAC_SEEK_SET)) {
                return 0;
            }

            oggbs->currentBytePos = offset;
            return 1;
        } else {
            drflac_uint64 offsetRemaining = offset;

            if (!oggbs->onSeek(oggbs->pUserData, (drflac_int64)0x7FFFFFFF, DRFLAC_SEEK_SET)) {
                return 0;
            }

            oggbs->currentBytePos = offset;

            offsetRemaining -= 0x7FFFFFFF;
            return drflac_oggbs__seek_physical(oggbs, offsetRemaining, DRFLAC_SEEK_CUR);
        }
    } else {
        drflac_uint64 offsetRemaining = offset;

        while (offsetRemaining >= 0x80000000) {
            if (!oggbs->onSeek(oggbs->pUserData, (drflac_int64)0x7FFFFFFF, DRFLAC_SEEK_CUR)) {
                return 0;
            }

            oggbs->currentBytePos += 0x7FFFFFFF;
            offsetRemaining -= 0x7FFFFFFF;
        }

        if (!oggbs->onSeek(oggbs->pUserData, (drflac_int64)offsetRemaining, DRFLAC_SEEK_CUR)) {
            return 0;
        }

        oggbs->currentBytePos += offsetRemaining;
        return 1;
    }
}