float func0(const void *a, const void *b) {
    float x = *(float *)a;
    float y = *(float *)b;
    x = x + y;
    y = x - y;
    x = x - y;
    return x - y;
}