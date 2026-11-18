static void reorder(int *a, int *b)
{
    int t;

    if (*a > *b) {
        t = *a;
        *a = *b;
        *b = t;
    }
}