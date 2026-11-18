void IndexToData(int32_t* a, int32_t* b, int32_t c) {
    *b = c & 0x3;
    *a = c >> 2;
}