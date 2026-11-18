int valid_bo_pre_v2(long long state) {
    if ((state & 0x14) == 0) {
        return 1;
    } else if ((state & 0x14) == 4) {
        return (state & 0x2) == 0;
    } else if ((state & 0x14) == 16) {
        return (state & 0x8) == 0;
    } else {
        return state == 0x14;
    }
}