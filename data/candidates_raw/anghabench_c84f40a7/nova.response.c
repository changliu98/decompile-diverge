static int func0(int byte) {
    int prio;

    if (byte >= 0x81 && byte < 0xff)
        prio = byte - 0x81;
    else
        prio = -1;

    return prio;
}