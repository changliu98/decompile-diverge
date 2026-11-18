drflac_bool32 drflac__seek_to_byte(drflac_bs *oggbs, drflac_uint64 offsetFromStart)
{
    drflac_bool32 result;

    do { if (oggbs != ((void*)0)) {} else { ___assert_fail("oggbs != ((void*)0)", "./func.c", 2881, "drflac_bool32 drflac__seek_to_byte(drflac_bs *, drflac_uint64)"); } } while (0);
    do { if (offsetFromStart > 0) {} else { ___assert_fail("offsetFromStart > 0", "./func.c", 2882, "drflac_bool32 drflac__seek_to_byte(drflac_bs *, drflac_uint64)"); } } while (0);

    if (offsetFromStart >= ((drflac_uint64)0x7FFFFFFF))
    {
        drflac_uint64 bytesRemaining = offsetFromStart;
        if (!oggbs->seek((oggbs)->pUserData, ((drflac_int32)0x7FFFFFFF), 0, oggbs))
        {
            result = 0;
        }
        else
        {
            bytesRemaining -= ((drflac_int32)0x7FFFFFFF);
            while (bytesRemaining >= ((drflac_int32)0x7FFFFFFF))
            {
                if (!oggbs->seek((oggbs)->pUserData, ((drflac_int32)0x7FFFFFFF), 1, oggbs))
                {
                    result = 0;
                    break;
                }

                bytesRemaining -= ((drflac_int32)0x7FFFFFFF);
            }

            if (bytesRemaining > 0)
            {
                if (!oggbs->seek((oggbs)->pUserData, (drflac_int32)bytesRemaining, 1, oggbs))
                {
                    result = 0;
                }
            }
            else
            {
                result = 1;
            }
        }
    }
    else
    {
        if (!oggbs->seek((oggbs)->pUserData, (drflac_int32)offsetFromStart, 0, oggbs))
        {
            result = 0;
        }
        else
        {
            result = 1;
        }
    }

    if (result)
    {
        drflac__reset_cache(oggbs);
    }

    return result;
}