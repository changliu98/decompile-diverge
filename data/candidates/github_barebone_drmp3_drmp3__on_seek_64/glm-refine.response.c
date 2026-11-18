define MAX_SEEK_STEP 0x7FFFFFFF

drmp3_bool32 __cdecl drmp3__on_seek_64(drmp3 *pMP3, drmp3_uint64 offset, drmp3_seek_origin origin)
{
    // If the offset fits within a 32-bit signed integer, just do a direct seek.
    if (offset <= MAX_SEEK_STEP)
        return drmp3__on_seek(pMP3, offset, origin);

    // For larger offsets, start by seeking to the maximum 32-bit step from the beginning.
    if (!drmp3__on_seek(pMP3, MAX_SEEK_STEP, DRMP3_SEEK_SET))
        return 0;

    drmp3_uint64 remaining_offset = offset - MAX_SEEK_STEP;

    // Seek the rest of the way in MAX_SEEK_STEP chunks.
    while (remaining_offset > 0)
    {
        drmp3_uint64 step = (remaining_offset > MAX_SEEK_STEP) ? MAX_SEEK_STEP : remaining_offset;

        if (!drmp3__on_seek(pMP3, step, DRMP3_SEEK_CUR))
            return 0;

        remaining_offset -= step;
    }

    return 1;
}