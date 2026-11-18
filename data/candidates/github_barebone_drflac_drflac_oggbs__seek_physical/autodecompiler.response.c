drflac_bool32 drflac_oggbs_seek(drflac_oggbs* oggbs, drflac_uint64 offset)
{



    if (oggbs->seekable) {
        if (oggbs->currentBytePos == oggbs->endOfStreamOffset) {
            if (offset >= oggbs->endOfStreamOffset) {
                return 1;
            }
        } else {
            if (oggbs->endOfStreamOffset != 0xFFFFFFFFFFFFFFFF && offset < oggbs->endOfStreamOffset) {
                if (drflac_oggbs__seek_physical(oggbs, offset, 0)) {
                    return 1;
                }
            }
        }
    }

    return drflac_oggbs__seek_physical(oggbs, offset, 0);
}