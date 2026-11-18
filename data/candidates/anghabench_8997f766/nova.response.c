int raid6_next_disk(int a, int b) {
    int c;
    a++;
    if (a < b)
        c = a;
    else
        c = 0;
    return c;
}