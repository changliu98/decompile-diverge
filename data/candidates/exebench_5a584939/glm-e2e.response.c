int path_source_set(int *p, int v) {
    *p = (*p & 0xfffffff1) | (v & 0xe);
    return *p;
}