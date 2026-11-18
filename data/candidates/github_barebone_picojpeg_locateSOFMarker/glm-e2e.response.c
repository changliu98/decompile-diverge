char locateSOFMarker() {
    char status;
    uint8_t marker;
    char result;

    // Call at 0x8
    status = nextMarker(&marker);
    if (status != 0) {
        result = status;
        goto end;
    }

    // Call at 0x29
    status = nextMarker(&marker);
    if (status != 0) {
        result = status;
        goto end;
    }

    // Switch statement based on marker
    // The assembly subtracts 0xC0 (0xffffff40 is -0xC0 in 32-bit signed) 
    // and checks if the result is > 9 (ja 0xab)
    switch (marker) {
        case 0xC0: // 0
            result = 0x25;
            break;
        case 0xC1: // 1
            result = 0x11;
            break;
        case 0xC2: // 2
            // Falls through to default (0xab)
        case 0xC3: // 3
            // Falls through to default (0xab)
        case 0xC4: // 4
            // Falls through to default (0xab)
        case 0xC5: // 5
            // Falls through to default (0xab)
        case 0xC6: // 6
            // Falls through to default (0xab)
        case 0xC7: // 7
            // Falls through to default (0xab)
        case 0xC8: // 8
            // Falls through to default (0xab)
        case 0xC9: // 9
            // Call at 0x7b
            status = skipVariableMarker();
            if (status != 0) {
                result = status;
                goto end;
            }
            result = 0;
            break;
        default:
            result = 0x14;
            break;
    }

end:
    return result;
}