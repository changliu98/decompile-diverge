static int drmp3__seek_long(drmp3* pMP3, unsigned long offset, int seekOrigin)
{
    int success;

    if (offset < 0x7FFFFFFF) {
        success = drmp3__on_seek(pMP3, (long)offset, seekOrigin);
    } else {

        if (!drmp3__on_seek(pMP3, 0x7FFFFFFF, 0)) {
            success = 0;
        } else {
            offset -= 0x7FFFFFFF;
            while (offset > 0) {
                long step = ((unsigned long)offset < 0x7FFFFFFF) ? (long)offset : 0x7FFFFFFF;
                if (!drmp3__on_seek(pMP3, step, 1)) {
                    success = 0;
                }

                offset -= step;
            }
            success = 1;
        }
    }

    return success;
}