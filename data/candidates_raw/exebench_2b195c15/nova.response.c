void func0(char **a, char **b) {
    char *c = *a;
    *a = *b;
    *b = c;
}