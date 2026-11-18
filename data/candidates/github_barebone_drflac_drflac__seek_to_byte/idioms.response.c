static _Bool drflac__seek_to_byte(struct drflac_bs *bs, long offsetFromStart)
{
    ((void) sizeof ((bs != ((void *)0)) ? 1 : 0), __extension__ ({ if (bs != ((void *)0)) ; else __assert_fail ("bs != ((void*)0)", "func.c", 4369, __extension__ __PRETTY_FUNCTION__); }));
    ((void) sizeof ((offsetFromStart > 0) ? 1 : 0), __extension__ ({ if (offsetFromStart > 0) ; else __assert_fail ("offsetFromStart > 0", "func.c", 4370, __extension__ __PRETTY_FUNCTION__); }));
    if (offsetFromStart > (0x7fffffff * 2U + 1U))
    {
        if (!bs->onSeek(bs->pUserData, (0x7fffffff * 2U + 1U), DRFLAC_SEEK_SET))
            return 0;
        offsetFromStart -= (0x7fffffff * 2U + 1U);
        while (offsetFromStart > (0x7fffffff * 2U + 1U))
        {
            if (!bs->onSeek(bs->pUserData, (0x7fffffff * 2U + 1U), DRFLAC_SEEK_CUR))
                return 0;
            offsetFromStart -= (0x7fffffff * 2U + 1U);
        }
        if (offsetFromStart > 0)
        {
            if (!bs->onSeek(bs->pUserData, offsetFromStart, DRFLAC_SEEK_CUR))
                return 0;
        }
    }
    else
    {
        if (!bs->onSeek(bs->pUserData, offsetFromStart, DRFLAC_SEEK_SET))
            return 0;
    }
    drflac__read_byte(bs);
    return 1;
}