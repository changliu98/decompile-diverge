int val_seg(uint16_t val)
{
    int ret = 0;

    val >>= 7;
    if (val & 0xF0) {
        ret += 4;
        val >>= 4;
    }
    if (val & 0x0C) {
        ret += 2;
        val >>= 2;
    }
    if (val & 0x02) {
        ret += 1;
    }

    return ret;
}