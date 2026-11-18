static int func0(int byte) {
    int value;

    if ((byte >= 0x40) && (byte < 0x80)) {
        value = byte - 0x40;
    } else if ((byte >= 0xa2) && (byte < 0x100)) {
        value = byte - 0x62;
    } else {
        value = -1;
    }

    return value;
}