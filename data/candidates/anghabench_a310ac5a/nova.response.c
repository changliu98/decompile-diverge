bool is_special_type(int x) {
    bool ret;
    x &= 0xF;
    ret = (x == a[0] || x == a[1]);
    return ret & 1;
}