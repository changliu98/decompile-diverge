drflac_bool32 drflac__seek_to_byte(drflac_bs *bs, drflac_uint64 offsetFromStart)
{
    drflac_uint64 offset;
    drflac_uint64 offsetRemaining;

    do { if (!(bs != ((void*)0))) { __assert_fail("bs != ((void*)0)", "func.c", 2881, "drflac_bool32 drflac__seek_to_byte(drflac_bs *, drflac_uint64)"); } } while (0);
    do { if (!(offsetFromStart > 0)) { __assert_fail("offsetFromStart > 0", "func.c", 2882, "drflac_bool32 drflac__seek_to_byte(drflac_bs *, drflac_uint64)"); } } while (0);







    offset = offsetFromStart;
    if (offset >= 0x80000000) {
        if (!bs->onSeek(bs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_SET)) {
            return 0;
        }

        offsetRemaining = offset - 0x7FFFFFFF;
        while (offsetRemaining >= 0x80000000) {
            if (!bs->onSeek(bs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_CUR)) {
                return 0;
            }

            offsetRemaining -= 0x7FFFFFFF;
        }

        if (offsetRemaining > 0) {
            if (!bs->onSeek(bs->pUserData, (int)offsetRemaining, DRFLAC_SEEK_CUR)) {
                return 0;
            }
        }
    } else {
        if (!bs->onSeek(bs->pUserData, (int)offset, DRFLAC_SEEK_SET)) {
            return 0;
        }
    }

    drflac__reset_cache(bs);

    return 1;
}