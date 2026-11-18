drmp3_bool32 drmp3__on_seek_64(drmp3* pMP3, drmp3_uint64 offset, drmp3_seek_origin origin)
{
    drmp3_uint64 offsetRemaining = offset;


    if (offset < 0x80000000) {
        return drmp3__on_seek(pMP3, (drmp3_int32)offset, origin);
    }


    if (!drmp3__on_seek(pMP3, 0x7FFFFFFF, DRMP3_SEEK_SET)) {
        return 0;
    }

    offsetRemaining -= 0x7FFFFFFF;

    while (offsetRemaining > 0) {
        drmp3_int32 offsetStep = (offsetRemaining < 0x80000000) ? (drmp3_int32)offsetRemaining : 0x7FFFFFFF;
        if (!drmp3__on_seek(pMP3, offsetStep, DRMP3_SEEK_CUR)) {
            return 0;
        }

        offsetRemaining -= offsetStep;
    }

    return 1;
}