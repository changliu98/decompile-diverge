int func0(int x[], int N)
{
    int i;
    int c = 0;
    i = 0;
    while (1) {
        if (i < N) {
            c = c + 1;
            i = i + 1;
        } else {
            break;
        }
    }
    return c;
}