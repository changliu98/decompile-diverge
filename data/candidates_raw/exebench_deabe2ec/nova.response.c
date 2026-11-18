void func0(char **a, char **b) {
    char *c;
    c = *a;
    *a = *b;
    *b = c;
}