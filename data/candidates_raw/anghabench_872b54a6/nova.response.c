static int func0(int byte) {
    int prio;

    if (byte >= 0x84 && byte < 0xd4)
        prio = byte - 0x84;
    else
        prio = -1;

    return prio;
}