void _vector_swap(char **a, char **b) {
    char *c = *a;
    *a = *b;
    *b = c;
}