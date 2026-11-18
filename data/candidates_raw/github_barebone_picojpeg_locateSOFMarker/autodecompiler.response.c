unsigned char readNextMarker(void)
{
    unsigned char ret;
    unsigned char marker;
    unsigned long sofType;

    ret = locateSOIMarker();
    if (ret != 0) {
        return ret;
    }

    ret = processMarkers(&marker);
    if (ret != 0) {
        return ret;
    }

    sofType = marker;
    switch (sofType) {
    case 0xC2:
        return 0x25;

    case 0xC0:
        ret = readSOFMarker();
        if (ret != 0) {
            return ret;
        }
        break;

    case 0xC9:
        return 0x11;

    case 0xC1:
        break;

    case 0xC3:
    default:
        return 0x14;
    }

    return 0;
}