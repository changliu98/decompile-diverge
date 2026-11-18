static size_t func0(size_t len) {
    size_t i = len - 16;
    size_t ret;

    if (i < 16) {
        ret = len_16[i];
    } else if (i < 32) {
        ret = 4;
    } else if (i < 64) {
        ret = 8;
    } else if (i < 128) {
        ret = 4;
    } else {
        ret = 8;
    }

    assert(ret <= sizeof(size_t) || sizeof(size_t) <= 4);

    return ret;
}