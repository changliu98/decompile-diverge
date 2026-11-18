define ERR_UNSUPPORTED_MARKER   20

uint8 __cdecl locateSOFMarker()
{
    uint8 marker; // BYREF

    uint8 status = locateSOIMarker();
    if (status) {
        return status;
    }

    status = processMarkers(&marker);
    if (status) {
        return status;
    }

    switch (marker)
    {
        case 0xC0: // SOF0 - Baseline DCT
            return readSOFMarker();
            
        case 0xC2: // SOF2 - Progressive DCT
            return ERR_PROGRESSIVE_JPEG;
            
        case 0xC9: // SOF9 - Extended sequential DCT, Arithmetic coding
            return ERR_ARITHMETIC_CODING;
            
        default:
            return ERR_UNSUPPORTED_MARKER;
    }
}