static int byte_row_johab_hangul(int byte) {
    int prio;

    if (byte >= 0x84 && byte < 0xd4)
        prio = byte - 0x84;
    else
        prio = -1;

    return prio;
}