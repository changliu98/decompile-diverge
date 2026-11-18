void long_swap(char **a, char **b) {
    char *c;
    c = *a;
    *a = *b;
    *b = c;
}