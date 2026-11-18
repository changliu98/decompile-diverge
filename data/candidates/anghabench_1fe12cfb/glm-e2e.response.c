int walNextHash(int h) {
    return (h + 1) & (HASHTABLE_NSLOT - 1);
}