drflac_bool32 drflac__seek_to_byte(drflac_bs *bitstream, drflac_uint64 targetOffset)
{
    drflac_bool32 seekResult;

    // Validate that the bitstream pointer is not null
    if (bitstream == (drflac_bs *)0x0) {
        __assert_fail("bs != ((void*)0)", "func.c", 0xb41,
                      "drflac_bool32 drflac__seek_to_byte(drflac_bs *, drflac_uint64)");
    }
    // Validate that the seek offset is greater than zero
    if (targetOffset == 0) {
        __assert_fail("offsetFromStart > 0", "func.c", 0xb42,
                      "drflac_bool32 drflac__seek_to_byte(drflac_bs *, drflac_uint64)");
    }

    // If the offset fits within a signed 32-bit integer, seek directly
    if (targetOffset < 0x80000000) {
        seekResult = (*bitstream->onSeek)(bitstream->pUserData, (int)targetOffset, DRFLAC_SEEK_SET);
        // If the seek operation fails, return false
        if (seekResult == 0) {
            return 0;
        }
    }
    // Otherwise, handle large offsets by seeking in chunks
    else {
        // Seek to the maximum positive signed 32-bit integer first
        seekResult = (*bitstream->onSeek)(bitstream->pUserData, 0x7fffffff, DRFLAC_SEEK_SET);
        // If the initial seek fails, return false
        if (seekResult == 0) {
            return 0;
        }

        // Loop to handle remaining bytes in chunks of 0x7fffffff
        do {
            drflac_uint64 remainingBytes = targetOffset - 0x7fffffff;
            // If remaining bytes fit in a signed 32-bit integer
            if (remainingBytes < 0x80000000) {
                // If there are bytes left to seek and the seek fails, return false
                if ((remainingBytes != 0) &&
                    ((seekResult = (*bitstream->onSeek)(bitstream->pUserData, (int)remainingBytes, DRFLAC_SEEK_CUR)) == 0)) {
                    return 0;
                }
                // All bytes have been processed, exit the loop
                break;
            }
            // Seek forward by the maximum chunk size
            seekResult = (*bitstream->onSeek)(bitstream->pUserData, 0x7fffffff, DRFLAC_SEEK_CUR);
            // Update the remaining offset
            targetOffset = remainingBytes;
        } while (seekResult != 0);
    }

    // Reset the bitstream cache after seeking
    drflac__reset_cache(bitstream);
    // Return true to indicate successful seek
    return 1;
}