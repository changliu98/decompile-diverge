static int func0(int a, int b, int c, int *out)
{
    int best, best_i;

    best = a;
    best_i = 1;
    if (best < b) {
        best = b;
        best_i = 2;
    }
    if (best < c) {
        best = c;
        best_i = 3;
    }
    *out = best;
    return best_i;
}