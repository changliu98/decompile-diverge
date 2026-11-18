void entry_clr_protected(unsigned long *ptr) {
    *ptr &= 0xFFFFFFFFFFFFFDFF;
    *ptr |= 0x0;
}