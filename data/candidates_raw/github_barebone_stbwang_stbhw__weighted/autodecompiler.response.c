int stbhw__weighted(int num_options, int *weights) {
    int total, choice, k;
    for (total = 0, k = 0; ; ++k) {
        if (k >= num_options)
            break;
        total += weights[k];
    }
    choice = ((rand() >> 4) % total);
    for (total = 0, k = 0; ; ++k) {
        if (k >= num_options)
            break;
        total += weights[k];
        if (choice < total)
            break;
    }
    { (void) ((k < num_options) || (__assert_fail ("k < num_options", "./func.c", 660, "int stbhw__weighted(int, int *)", 0))); };
    return k;
}