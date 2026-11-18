void swap_l(char **a, char **b) {
    char *c;
    c = *a;
    *a = *b;
    *b = c;
}