list func0(list *l, int start, int end, int *length) {
    int i = 0, j = 0;
    for (i; i < end; i++) {
        if (strlen(l->buf[i]) == (size_t)start) {
            list1.buf[j++] = l->buf[i];
        }
    }
    *length = j;
    return list1;
}