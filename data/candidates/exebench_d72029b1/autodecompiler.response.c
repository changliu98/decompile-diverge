void test1(short n, int *a)
{
    short i = 0;
    while(1) {
        if (i < n) {
            i++;
            a[i] = 0;
            i++;
        } else {
            return;
        }
    }
}